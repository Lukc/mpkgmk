
#ifndef _H_MODULES
#define _H_MODULES

#include "recipe.h"
#include "configuration.h"

#define MODULE_FAILED -1
#define MODULE_USELESS 0
#define MODULE_SUCCEEDED 1

typedef int ModuleFunction(RecipeElement *recipe, Configuration *configuration);
typedef int ModuleSourceFunction(Source *source, Configuration *configuration);
typedef int ModuleOnLoadFunction(Configuration *configuration);

typedef struct Module {
	char *name; /* For debug and info messages and assimilated */

	/* Sources collection tools. */
	ModuleSourceFunction *downloader;
	ModuleSourceFunction *extractor;

	/* Construction tools. */
	ModuleFunction *configure;
	ModuleFunction *build;
	ModuleFunction *install;

	/* Packages building. */
	ModuleFunction *assembler;
} Module;

Module** load_modules();

#endif

