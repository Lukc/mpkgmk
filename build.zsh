#!/usr/bin/env zsh

# TODO:
#	- Make more checks about whether the “things” built and installed are C.
#	  (stuff *will* break if you add non-C things as targets)
#	- Clean some more (or a lot). I mean, this script could even be reused if
#	  it were cleaner, more readable and somewhat more documented.
#
# WARNINGS and LIMITATIONS:
# 	- Using a relative path in DESTDIR= *will* fail.
#

# Script output

function info {
	echo "${fg_bold[green]}-- ${fg_bold[white]}$@${reset_color}"
}

function warning {
	echo "${fg_bold[yellow]}-- $@${reset_color}" >&2
}

function error {
	echo "${fg_bold[red]}-- ERROR: $@${reset_color}" >&2
}

# Makefiles’ output

function write {
	echo "$@" >> $Makefile
}

function CC {
	echo "${fg_bold[blue]}  [CC]    ${fg_bold[white]}$@${reset_color}"
}

function LD {
	echo "${fg_bold[green]}  [LD]    ${fg_bold[white]}$@${reset_color}"
}

function IN {
	echo "${fg_bold[red]}  [IN]    ${fg_bold[white]}$@${reset_color}"
}

function LN {
	echo "${fg_bold[yellow]}  [LN]    ${fg_bold[white]}$@${reset_color}"
}

function RM {
	echo "${fg_bold[white]}  [RM]    ${fg_bold[white]}$@${reset_color}"
}

function DIR {
	echo "${fg_bold[magenta]}  [DIR]   ${fg_bold[white]}$@${reset_color}"
}

function TAR {
	echo "${fg_bold[yellow]}  [TAR]   ${fg_bold[white]}$@${reset_color}"
}

# Specialized helpers

function subdirs {
	write -n "\t${Q}for i in ${subdirs[@]}; do (cd \"\$\$i\" && $MAKE"
	write -n ' Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)"'
	for name path in ${prefixes[@]}; do
		write -n " ${name}=\"\$(${name})\""
	done
	if (( $# > 0 )); then
		write -n " $@"
	fi
	write '); done'
}

function get_distfiles {
	for file in "${dist[@]}" $(echo ${sources[@]}) $(echo ${depends[@]}); do
		echo "$file"
	done

	typeset -a src
	src=($(echo ${sources[@]}))
	for file in ${src[@]}; do
		typeset file="${file%.c}.h"
		if [[ -e "$file" ]]; then
			echo "$file"
		fi
	done

	for dir in ${subdirs[@]}; do
		(
			unset dist sources depends subdirs
			typeset -a dist
			typeset -A sources depends

			cd "$dir"
			. ./project.zsh
			for file in $(get_distfiles); do
				local file="${dir}/${file}"
				while [[ "$file" =~ "\.\./" ]]; do
					error "${file}"
					file="${file/[a-z]*\/\.\.\//}"
					error " -> ${file}"
				done

				echo "${file}"
			done
		)
	done
}

function exists {
	[[ "$(whence -w ${1})" != "${1}: none" ]]
}

function duplicated {
	local elem="$1"
	local count=0
	shift 1
	local i
	for i in $@; do
		if [[ "$elem" == "$i" ]]; then
			((count++))

			if (( $count > 1 )); then
				return 0
			fi
		fi
	done

	return 1
}

for i in build/*.zsh; do
	. $i
done

##
# And so it begins
##

function main {
	typeset -a prefixes directories
	typeset -A ldflags cflags sources type depends install

	prefixes=(
		PREFIX '/usr/local'
		BINDIR '$(PREFIX)/bin'
		LIBDIR '$(PREFIX)/lib'
		SHAREDIR '$(PREFIX)/share'
		INCLUDEDIR '$(PREFIX)/include'
	)

	if [[ -f project.zsh && -r project.zsh ]]; then
		. ./project.zsh
	else
		error "No “project.zsh” found in $(pwd)."
		exit 1
	fi

	: > $Makefile

	if [[ -n "$package" && -n "$version" ]]; then
		export package version

		write "PACKAGE = '$package'"
		write "VERSION = '$version'"
		write
	fi

	for prefix path in ${prefixes[@]}; do
		write "$prefix := $path"
	done

	write

	write "CFLAGS := ${CFLAGS}"
	write "LDFLAGS := ${LDFLAGS}"
	write

	write "Q := @"
	write

	write -n "all: "
	(( ${#targets[@]} > 0 )) && write -n " ${targets[@]}"
	(( ${#subdirs[@]} > 0 )) && write -n " subdirs"
	write "\n"

	for target in ${targets[@]}; do
		(
			typeset -a src
			src=($(echo ${sources[$target]}))
			local installdir="${install[$target]}"

			if exists "${type[$target]}.build"; then
				${type[$target]}.build
			else
				error "No predefined rule for the following type: ${type[$target]}"
				error "  (expect trouble, nothing’s gonna work!)"
			fi

			if exists "${type[$target]}.install"; then
				${type[$target]}.install
			else
				if [[ -z "${installdir}" ]]; then
					error "No install[${type[${target}]}] and no default installation directory."
					error "Your “install” rule will be broken!"
				else
					write "${target}.install: \$(DESTDIR)${installdir}"
					write "\t@echo '$(IN ${installdir}/${target})'"
					write "\t${Q}install -m755 $target \$(DESTDIR)${installdir}/$target"
					write
				fi
			fi

			if exists "${type[$target]}.clean"; then
				${type[$target]}.clean
			else
				write "${target}.clean:"
				write "\t@echo '$(RM ${target})'"
				write "\t${Q}rm -f ${target}"
				write
			fi

			if exists "${type[$target]}.uninstall"; then
				${type[$target]}.uninstall
			else
				write "${target}.uninstall:"
				write "\t@echo '$(RM "${installdir}/${target}")'"
				write "\t${Q}rm -f '\$(DESTDIR)${installdir}/${target}'"
				write
			fi
		)
	done

	for dir in ${directories[@]}; do
		write "\$(DESTDIR)${dir}:"
		write "\t@echo '$(DIR ${dir})'"
		write "\t${Q}mkdir -p \$(DESTDIR)${dir}"
	done

	for dir __ in ${prefixes[@]}; do
		write "\$(DESTDIR)\$(${dir}):"
		write "\t@echo '$(DIR "\$(${dir})")'"
		write "\t${Q}mkdir -p \$(DESTDIR)\$(${dir})"
	done

	(( ${#subdirs[@]} > 0 )) && {
		write "subdirs:"
		subdirs
		write
	}

	write -n "install: subdirs.install"
	for target in ${targets[@]}; do
		write -n " ${target}.install"
	done
	write "\n"

	write "subdirs.install:"
	subdirs install
	write

	write -n "uninstall: subdirs.uninstall"
	for target in ${targets[@]}; do
		write -n " ${target}.uninstall"
	done
	write "\n"

	write "subdirs.uninstall:"
	subdirs uninstall
	write

	write -n "clean:"
	(( ${#targets[@]} > 0 )) && {
		for target in ${targets[@]}; do
			write -n " ${target}.clean"
			(
				typeset -a src
				src=($(echo ${sources[$target]}))

				for file in ${src[@]}; do
					write -n " ${file%.c}.o.clean"
				done
			)
		done
	}
	write
	(( ${#subdirs[@]} > 0 )) && subdirs clean
	write

	write "distclean: clean"
	(( ${#subdirs[@]} > 0 )) && subdirs distclean
	write

	if $root; then
		write "dist: dist-gz dist-xz dist-bz2"
		write "\t"$Q'rm -- $(PACKAGE)-$(VERSION)'
		write

		write "distdir:"
		write "\t"$Q'rm -rf -- $(PACKAGE)-$(VERSION)'
		write "\t"$Q'ln -s -- . $(PACKAGE)-$(VERSION)'
		write

		typeset -a distfiles
		distfiles=($(get_distfiles))
		local i

		for i in {1..${#distfiles[@]}}; do
			if duplicated "${distfiles[${i}]}" "${distfiles[@]}"; then
				distfiles[${i}]=
			fi
		done

		for i flag in gz z xz J bz2 j; do
			write "dist-${i}: \$(PACKAGE)-\$(VERSION).tar.$i"
			write "\$(PACKAGE)-\$(VERSION).tar.$i: distdir"
			write "\t@echo '$(TAR "\$(PACKAGE)-\$(VERSION).tar.$i")'"
			write "\t${Q}tar c${flag}f \$(PACKAGE)-\$(VERSION).tar.$i \\"
			for i in {1..${#distfiles}}; do
				if [[ -n "${distfiles[$i]}" ]]; then
					write -n "\t\t\$(PACKAGE)-\$(VERSION)/${distfiles[$i]}"
					if (( i != ${#distfiles} )); then
						write " \\"
					fi
				fi
			done
			write "\n"
		done
	fi

	for i in ${subdirs[@]}; do
		(
			cd $i
			unset subdirs targets dist sources ldflags depends install type
			typeset -A sources ldflags depends install type
			typeset -a targets dist
			root=false main $i
		)
	done

	write ".PHONY: all subdirs clean distclean dist install uninstall"
	write
}

export Makefile=Makefile
export MAKE='$(MAKE)'
export Q='$(Q)'

while (($# > 0)); do
	case "$1" in
		-c|--colors)
			autoload -U colors
			colors
		;;
		-h|--help)
			echo "usage: $0 [OPTIONS]"
			echo
			echo "Options:"
			echo "   -h, --help           Print this help message."
			echo "   -c, --colors         Use colors in your Makefiles"
			echo "                        (relies on zsh/colors and your current \$TERM)"
		;;
		*)
			error "unrecognised parameter: $1"
			return 1
		;;
	esac

	shift 1
done

echo "Generating Makefiles..."
root=true main

