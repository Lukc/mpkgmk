#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "ui.h"
#include "opts.h"
#include "recipe.h"
#include "modules.h"
#include "workdir.h"
#include "download.h"
#include "extraction.h"
#include "configuration.h"
#include "package.h"
#include "build.h"
#include "assemble.h"
#include "error.h"

int main(int argc, char *argv[]) {
	RecipeElement *recipe;
	Module **modules;
	Configuration *configuration;
	Source **sources;
	Package *packages;
	char *work_dir;

	recipe = load_recipe("./package.yaml");

	modules = load_modules();

	/* FIXME: Configuration should come before the recipe. But it should
	 *        be processed again once the recipe is available, to 
	 *        allow stuff like mpkgmk-$name as work dir or whatever */
	configuration = load_configuration(recipe);
	parse_options(argc, argv, configuration);

	sources = get_sources(recipe);
	packages = recipe_to_packages(recipe);

	/*
	 * TODO HERE:
	 * 	- check configuration and recipe validity
	 * 	- check for the existence of packages and sources directories
	 */

	if (!modules) {
		error("No module could be loaded. You’re kinda screwed.");
		exit(1);
	}

	work_dir = configuration->working_directory;
	create_work_dir(work_dir);

	if (sources) {
		download(recipe, modules, configuration, sources);

		extract(recipe, modules, configuration, sources);
	}

	if (chdir(work_dir) == -1) {
		perror("chdir");
		exit(ERROR_BUILDING_FAILED);
	}

	build(recipe, modules, configuration);

	/* More stuff will have to be done about this once splits will
	 * become a priority. */
	assemble(recipe, packages, modules, configuration);

	/* FIXME: Success is assumed, for now */
	modules_on_exit(configuration, modules, 1);
	/* FIXME: Cleaning (memory, work dir, sources, whatever) *should* happen here. If you see what I mean. */

	/* FIXME: Great. When am I going to free its content, then? */
	free(recipe);

	return 0;
}

