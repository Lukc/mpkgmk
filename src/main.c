#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "ui.h"
#include "recipe.h"
#include "modules.h"
#include "workdir.h"
#include "download.h"
#include "extraction.h"
#include "configuration.h"
#include "build.h"
#include "assemble.h"

int main() {
	RecipeElement *recipe;
	Module **modules;
	Configuration *configuration;
	Source **sources;
	char *work_dir;

	recipe = load_recipe("./package.yaml");

	modules = load_modules();
	configuration = load_configuration(recipe);
	sources = get_sources(recipe);

	/*
	 * TODO HERE:
	 * 	- check configuration and recipe validity
	 * 	- check for the existence of packages and sources directories
	 */

	if (!modules) {
		error("No module could be loaded. You’re kinda screwed.");
		exit(1);
	}

	if (sources) {
		download(recipe, modules, configuration, sources);

		work_dir = configuration->working_directory;
		create_work_dir(work_dir);

		extract(recipe, modules, configuration, sources);
	}

	chdir(work_dir);

	build(recipe, modules, configuration);

	/* More stuff will have to be done about this once splits will
	 * become a priority. */
	assemble(recipe, modules, configuration);

	/* FIXME: Success is assumed, for now */
	modules_on_exit(configuration, modules, 1);
	/* FIXME: Cleaning (memory, work dir, sources, whatever) *should* happen here. If you see what I mean. */

	/* FIXME: Great. When am I going to free its content, then? */
	free(recipe);

	return 0;
}

