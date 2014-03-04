#!/usr/bin/env zsh

function info {
	echo "-- $@"
}

function warning {
	echo "-- $@" >&2
}

function error {
	echo "-- ERROR: $@" >&2
}

function write {
	echo "$@" >> $Makefile
}

function subdirs {
	write -n "\t${Q}for i in ${subdirs[@]}; do (cd \"\$\$i\" && $MAKE"
	write -n ' Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"'
	for name path in ${prefixes[@]}; do
		write -n " ${name}=\"\$(${name})\""
	done
	if (( $# > 0 )); then
		write -n " $@"
	fi
	write '); done'
}

function get_distfiles {
	for file in ${dist[@]} ${sources[@]} ${depends[@]}; do
		echo "$file"
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

function main {
	typeset -a prefixes
	typeset -A ldflags cflags sources type depends install

	prefixes=(
		PREFIX '/usr/local'
		BINDIR '$(PREFIX)/bin'
		LIBDIR '$(PREFIX)/lib'
	)

	if [[ -f project.zsh && -r project.zsh ]]; then
		. ./project.zsh
	else
		error "No “project.zsh” found in $(pwd)."
		exit 1
	fi

	##
	# And so it begins
	##

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
				write "\t@echo '  [LD]  ${target}'"
				write "\t$Q\$(CC) -o ${target} \$(CFLAGS) \$(LDFLAGS) ${ldflags[$target]} ${src[@]//.c/.o}"
				write

				for i in ${src[@]}; do
					write "${i%.c}.o: ${i} $([[ -e ${i%.c}.h ]] && echo "${i%.c}.h")"
					write "\t@echo '  [CC]  ${i%.c}.o'"
					write "\t$Q\$(CC) \$(CFLAGS) ${cflags[$target]} -c ${i}"
					write
				done
			elif [[ ${type[$target]} == "dynamic-library" ]]; then
				for i in ${src[@]}; do
					write -n " ${i%.*}.o"
				done
				write " ${depends[$target]}"
				write "\t@echo '  [LD]  ${target}'"
				write "\t$Q\$(CC) -o ${target} -fPIC -shared \$(CFLAGS) \$(LDFLAGS) ${ldflags[$target]} ${src[@]//.c/.o}"
				write
				write

				for i in ${src[@]}; do
					write "${i%.c}.o: ${i} $([[ -e ${i%.c}.h ]] && echo "${i%.c}.h")"
					write "\t@echo '  [CC]  ${i%.c}.o'"
					write "\t$Q\$(CC) -fPIC \$(CFLAGS) ${cflags[$target]} -c ${i}"
					write
				done
			else
				error "Unknown type: ${type[$target]}"
			fi
		)
	done

	(( ${#subdirs[@]} > 0 )) && {
		write "subdirs:"
		subdirs
		write
	}

	write "install:"
	write "\t@echo 'Well, it does not work, at this point.'; false"

	write "clean:"
	(( ${#targets[@]} > 0 )) && write "\trm -f *.o ${targets[@]}"
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
		write "\t@echo '  [TAR]  \$(PACKAGE)-\$(VERSION).tar.$i'"
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
}

export Makefile=Makefile
export MAKE='$(MAKE)'
export Q='$(Q)'

echo "Generating Makefiles..."
main
