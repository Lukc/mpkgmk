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
	for file in ${dist[@]} $(echo ${sources[@]}) $(echo ${depends[@]}); do
		echo "$file"
	done

	typeset -la src
	src=($(echo ${sources[@]}))
	for file in ${src[@]}; do
		typeset -l file="${file%.c}.h"
		if [[ -e "$file" ]]; then
			echo "$file"
		fi
	done

	for dir in ${subdirs[@]}; do
		(
			unset sources depends subdirs
			typeset -a dist
			typeset -A sources depends

			cd "$dir"
			. ./project.zsh
			for file in $(get_distfiles); do
				echo "$dir/$file"
			done
		)
	done
}

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
	)

	if [[ -f project.zsh && -r project.zsh ]]; then
		. ./project.zsh
	else
		error "No “project.zsh” found in $(pwd)."
		exit 1
	fi

	: > $Makefile

	if [[ -n "$package" && -n "$version" ]]; then
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
		write -n "${target}:"

		(
			typeset -la src
			src=($(echo ${sources[$target]}))

			if [[ ${type[$target]} == "binary" ]]; then
				for i in ${src[@]}; do
					write -n " ${i%.*}.o"
				done
				write " ${depends[$target]}"
				write "\t@echo '$(LD ${target})'"
				write "\t$Q\$(CC) -o ${target} \$(CFLAGS) \$(LDFLAGS) ${ldflags[$target]} ${src[@]//.c/.o}"
				write

				for i in ${src[@]}; do
					write "${i%.c}.o: ${i} $([[ -e ${i%.c}.h ]] && echo "${i%.c}.h")"
					write "\t@echo '$(CC ${i%.c}.o)'"
					write "\t$Q\$(CC) \$(CFLAGS) ${cflags[$target]} -c ${i}"
					write

					write "${i%.c}.o.clean:"
					write "\t@echo '$(RM ${i%.c}.o)'"
					write "\t${Q}rm -f ${i%.c}.o"
					write
				done

				local installdir="${install[$target]:-\$(BINDIR)}"
				write "${target}.install: \$(DESTDIR)${installdir}"
				write "\t@echo '$(IN ${installdir}/${target})'"
				write "\t${Q}install -m755 $target \$(DESTDIR)${installdir}/$target"
				write
			elif [[ ${type[$target]} == "dynamic-library" ]]; then
				for i in ${src[@]}; do
					write -n " ${i%.*}.o"
				done
				write " ${depends[$target]}"
				write "\t@echo '$(LD ${target})'"
				write "\t$Q\$(CC) -o ${target} -fPIC -shared \$(CFLAGS) \$(LDFLAGS) ${ldflags[$target]} ${src[@]//.c/.o}"
				write
				write

				for i in ${src[@]}; do
					write "${i%.c}.o: ${i} $([[ -e ${i%.c}.h ]] && echo "${i%.c}.h")"
					write "\t@echo '$(CC ${i%.c}.o)'"
					write "\t$Q\$(CC) -fPIC \$(CFLAGS) ${cflags[$target]} -c ${i}"
					write

					write "${i%.c}.o.clean:"
					write "\t@echo '$(RM ${i%.c}.o)'"
					write "\t${Q}rm -f ${i%.c}.o"
					write
				done

				# Add a add-symlinks option?
				local installdir="${install[$target]:-\$(LIBDIR)}"
				write "${target}.install: \$(DESTDIR)${installdir}"
				write "\t@echo '$(IN ${installdir}/${target})'"
				write "\t${Q}install -m755 $target \$(DESTDIR)${installdir}/$target"
				write
			elif [[ ${type[$target]} == "script" ]]; then
				write
				write "\t@echo '  [  ]    ${target}'"
				write

				local installdir="${install[$target]:-\$(SHAREDIR)/$package}"
				write "${target}.install: \$(DESTDIR)${installdir}"
				write "\t@echo '$(IN ${installdir}/${target})'"
				write "\t${Q}install -m755 $target \$(DESTDIR)${installdir}/$target"
				write
			else
				error "Unknown type: ${type[$target]}"
				error "  (expect trouble, nothing’s gonna work!)"
			fi

			# FIXME: Just find a better way to handle this already.
			if [[ "${type[$target]}" == "script" ]]; then
				write "${target}.clean:"
			else
				write "${target}.clean:"
				write "\t@echo '$(RM ${target})'"
				write "\t${Q}rm -f ${target}"
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

	write -n "clean:"
	(( ${#targets[@]} > 0 )) && {
		for target in ${targets[@]}; do
			write -n " ${target}.clean"
			(
				typeset -la src
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

	write "dist: dist-gz dist-xz dist-bz2"
	write "\t"$Q'rm -- $(PACKAGE)-$(VERSION)'
	write

	write "distdir:"
	write "\t"$Q'rm -rf -- $(PACKAGE)-$(VERSION)'
	write "\t"$Q'ln -s -- . $(PACKAGE)-$(VERSION)'
	write

	for i flag in gz z xz J bz2 j; do
		write "dist-${i}: \$(PACKAGE)-\$(VERSION).tar.$i"
		write "\$(PACKAGE)-\$(VERSION).tar.$i: distdir"
		write "\t@echo '$(TAR "\$(PACKAGE)-\$(VERSION).tar.$i")'"
		write "\t${Q}tar c${flag}f \$(PACKAGE)-\$(VERSION).tar.$i \\"
		typeset -la distfiles
		distfiles=($(get_distfiles))
		for i in {1..${#distfiles}}; do
			write -n "\t\t\$(PACKAGE)-\$(VERSION)/${distfiles[$i]}"
			if (( i != ${#distfiles} )); then
				write " \\"
			fi
		done
		write "\n"
	done

	for i in ${subdirs[@]}; do
		(
			cd $i
			unset package version subdirs targets dist sources ldflags depends install type
			typeset -A sources ldflags depends install type
			typeset -a targets dist
			main $i
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
main

