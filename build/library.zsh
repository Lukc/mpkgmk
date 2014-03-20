
# FIXME: Build static libraries as well.
# FIXME: Add symlinks at installation.

function library.build {
	write "${target}: ${target}.so"
	write

	target="${target}.so" dynamic-library.build
}

function library.install {
	local install="${install[$target]:-\$(LIBDIR)}"
	local realtarget

	typeset -a symlinks
	if [[ -z "$version" ]]; then
		realtarget="${target}.so"
		symlinks=()
	else
		realtarget="${target}.so.${version}"
		for i in ".${version%.*}" ".${version%.*.*}" ""; do
			symlinks+=("${target}.so$i")
		done
	fi

	write -n "${target}.install: "
	for i in ${symlinks[@]}; do
		write -n " ${i}.install"
	done
	write "\n"

	write "${target}.so.${version}.install: ${target}.so \$(DESTDIR)${install}"
	write "\t@echo '$(IN "${install}/${realtarget}")'"
	write "\t${Q}install -m755 $target.so \$(DESTDIR)${install}/${realtarget}"
	write

	for i in ${symlinks[@]}; do
		write "${i}.install: ${target}.so.${version}.install"
		write "\t@echo '$(LN "${install}/${i}")'"
		write "\t${Q}ln -sf '${install}/${target}.so.${version}' '\$(DESTDIR)/${install}/${i}'"
		write
	done
}

function library.uninstall {
	local install="${install[$target]:-\$(LIBDIR)}"
	local realtarget

	if [[ -z "$version" ]]; then
		write "${target}.so.uninstall:"
		write "\t@echo '$(RM ${install}/${target}.so)'"
		write "\t${Q}rm -f '\$(DESTDIR)${install}/${target}.so'"
		write
	else
		write -n "${target}.uninstall: "
		for i in "" ".${version%.*.*}" ".${version%.*}" ".${version}"; do
			write -n " ${target}.so${i}.uninstall"
		done
		write "\n"

		for i in "" ".${version%.*.*}" ".${version%.*}" ".${version}"; do
			write "${target}.so${i}.uninstall:"
			write "\t@echo '$(RM ${install}/${target}.so${i})'"
			write "\t${Q}rm -f '\$(DESTDIR)${install}/${target}.so${i}'"
			write
		done
	fi

}

function library.clean {
	binary.clean
}

