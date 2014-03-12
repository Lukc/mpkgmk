#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpkgmk_private.h>

int
mpkgmk_assembler(RecipeElement *recipe, Package *packages, Configuration *configuration) {
	char *cmd, *name, *versionstr, *releasestr, *filename;

	if (!strcmp(configuration->assembler, "pkgutils")) {
		name = packages[0].name;
		versionstr = packages[0].version;

		releasestr = (char*) malloc(sizeof(char) * 3);
		snprintf(releasestr, 3, "%i", packages[0].release);

		filename = (char*) malloc(sizeof(char) * (
			4 +
			strlen(configuration->packages_directory) +
			strlen(".pkg.tar.xz") +
			strlen(name) +
			strlen(versionstr) +
			strlen(releasestr)
		));
		sprintf(
			filename, "%s/%s#%s-%s%s",
			configuration->packages_directory,
			name, versionstr, releasestr,
			".pkg.tar.xz"
		);

		cmd = (char*) malloc(sizeof(char) * (
			1 +
			strlen(filename) +
			strlen(configuration->working_directory) +
			strlen("(cd ''; tar cJf '' *)")
		));
		sprintf(
			cmd, "(cd '%s'; tar cJf '%s' *)",
			configuration->working_directory,
			filename
		);

		if (system(cmd) == 0)
			return MODULE_SUCCEEDED;
		else
			return MODULE_FAILED;
	}

	return MODULE_USELESS;
}

