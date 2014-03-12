#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "configuration.h"

Configuration*
load_configuration(RecipeElement *recipe) {
	Configuration *configuration;
	char *name;

	configuration = (Configuration*) malloc(sizeof(Configuration));

	/* Defaults */
	configuration->download = 1;

	configuration->assembler = "pkgutils";

	/* FIXME: Too many unchecked return values around here.
	 *        It’s going to have to be rewritten when a real configuration
	 *        is implemented anyway, but… */
	configuration->sources_directory = (char*) malloc(sizeof(char) * 1024);
	configuration->packages_directory = (char*) malloc(sizeof(char) * 1024);

	getcwd(configuration->packages_directory, 1024);
	getcwd(configuration->sources_directory, 1024);

	name = recipe_alist_get(recipe->data.alist, "name")->data.string;
	configuration->working_directory = (char*) malloc(sizeof(char) * (
		strlen("/tmp/mpkgmk-") +
		strlen(name) + 1
	));
	sprintf(configuration->working_directory, "/tmp/mpkgmk-%s", name);

	return configuration;
}

