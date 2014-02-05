#include <stdlib.h>

#include "build.h"
#include "ui.h"
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

		if (stage > 1 && !was_built) {
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

