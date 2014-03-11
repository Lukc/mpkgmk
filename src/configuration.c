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

	configuration->sources_directory = ".";
	configuration->assembler = "pkgutils";
	configuration->packages_directory = ".";

	name = recipe_alist_get(recipe->data.alist, "name")->data.string;
	configuration->working_directory = (char*) malloc(sizeof(char) * (
		strlen("/tmp/mpkgmk") +
		strlen(name) + 2
	));
	sprintf(configuration->working_directory, "/tmp/mpkgmk/%s", name);

	return configuration;
}

