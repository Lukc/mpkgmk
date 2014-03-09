#include <stdlib.h>
#include <string.h>

#include "assemble.h"
#include "error.h"

void
assemble(RecipeElement *recipe, Module **modules, Configuration *configuration) {
	int i, ret;
	Module *module;

	i = 0;
	while (modules[i]) {
		module = modules[i];
		if (module->assembler) {
			ret = module->assembler(recipe, configuration);

			if (ret == MODULE_FAILED) {
				error("Oops! Assembling failed. :(((");

				exit(ERROR_PACKAGING_FAILED);
			} else if (ret == MODULE_SUCCEEDED)
				return;
		}

		i++;
	}

	/* We should never be here. */
	/* FIXME: Actually make sure we’re never going to end up here before starting to build anything. */
	error("No module matches the assembler specified in your configuration.");
	exit(ERROR_BROKEN_CONFIGURATION);
}


