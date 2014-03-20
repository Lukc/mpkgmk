
function dynamic-library.build {
	write -n "${target}:"
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
	done
}

function dynamic-library.install {
	# Add a add-symlinks option?
	local install="${install[$target]:-\$(LIBDIR)}"
	write "${target}.install: ${target} \$(DESTDIR)${install}"
	write "\t@echo '$(IN ${install}/${target})'"
	write "\t${Q}install -m755 $target \$(DESTDIR)${install}/$target"
	write
}

function dynamic-library.uninstall {
	# Add a add-symlinks option?
	local install="${install[$target]:-\$(LIBDIR)}"
	write "${target}.uninstall:"
	write "\t@echo '$(RM ${install}/${target})'"
	write "\t${Q}rm -f '\$(DESTDIR)${install}/${target}'"
	write
}

function dynamic-library.clean {
	write "${target}.clean:"
	write "\t@echo '$(RM ${target})'"
	write "\t${Q}rm -f ${target}"
	write

	for i in ${src[@]}; do
		write "${i%.c}.o.clean:"
		write "\t@echo '$(RM ${i%.c}.o)'"
		write "\t${Q}rm -f ${i%.c}.o"
		write
	done
}

