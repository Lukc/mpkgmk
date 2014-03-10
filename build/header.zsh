
function header.build {
	write "${target}:"
	write "\t@echo '  [  ]    ${target}'"
	write
}

function header.clean {
	write "${target}.clean:"
	write
}

function header.install {
	local install="${install[$target]:-\$(INCLUDEDIR)}"
	write "${target}.install: ${target}"
	write "\t@echo '$(IN "${install}/${target}")'"
	write "\t${Q}install -m0755 ${target} \$(DESTDIR)${install}/${target}"
	write
}

function header.uninstall {
	local install="${install[$target]:-\$(INCLUDEDIR)}"
	write "${target}.uninstall:"
	write "\t@echo '$(RM ${install}/${target})'"
	write "\t${Q}rm -f '\$(DESTDIR)${install}/${target}'"
	write
}

