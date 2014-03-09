#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <mpkgmk_private.h>

#include "build.h"
#include "error.h"

void
build(RecipeElement *recipe, Module **modules, Configuration *configuration) {
	int i, ret, was_built, stage;
	Module *module;


	/* Stages:
	 *	- 1: Configuration.   Optional.
	 *	- 2: Build.           Mandatory.
	 *	- 3: Installation.    Mandatory.
	 */

	stage = 1;
	while (stage <= 3) {
		i = 0;
		was_built = 0;

		while (modules[i]) {
			module = modules[i];
			if (module->configure) {
				if (stage == 1)
					ret = module->configure(recipe, configuration);
				else if (stage == 2)
					ret = module->build(recipe, configuration);
				else if (stage == 3)
					ret = module->install(recipe, configuration);

				if (ret == MODULE_SUCCEEDED) {
					was_built = 1;
					break;
				} else if (ret == MODULE_FAILED) {
					if (stage == 1)
						error("Configuration failed.");	
					else if (stage == 2) {
						error("Building failed.");	
						exit(ERROR_BUILDING_FAILED);
					} else if (stage == 3) {
						error("Installation failed.");	
						exit(ERROR_BUILDING_FAILED);
					}
				} else if (ret == MODULE_USELESS) {
					/* ignore */
				} else {
					error("Broken module.");
					exit(ERROR_BROKEN_MODULE);
				}
			}

			i++;
		}

		if (!was_built) {
			char *code = NULL;
			if (stage == 1)
				code = recipe_alist_get(recipe->data.alist, "configure")->data.string;
			else if (stage == 2)
				code = recipe_alist_get(recipe->data.alist, "build")->data.string;
			else if (stage == 3)
				code = recipe_alist_get(recipe->data.alist, "install")->data.string;

			if (code) {
				if (shell(code) == 0)
					was_built = 1;
				else {
					error("An error occured while building the software.");

					exit(ERROR_BUILDING_FAILED);
				}
			}
		}

		if (!was_built && stage > 1) {
			if (stage == 2)
				error("No module could build your software. Specify build: in your recipe");
			else if (stage == 3)
				error("No module could install your software. Specify install: in your recipe");

			error(" or add a module supporting this buid system.");

			exit(ERROR_BUILDING_FAILED);
		}

		stage++;
	}
}

