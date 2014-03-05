
#ifndef _H_MODULES
#define _H_MODULES

#include "recipe.h"
#include "configuration.h"

#define MODULE_FAILED -1
#define MODULE_USELESS 0
#define MODULE_SUCCEEDED 1

typedef int (*ModuleFunction)(RecipeElement*, Configuration*);
typedef int (*ModuleSourceFunction)(Source*, Configuration*);
typedef int (*ModuleOnLoadFunction)(Configuration*);
typedef int (*ModuleOnExitFunction)(Configuration*, int);

typedef struct Module {
	char *name; /* For debug and info messages and assimilated */

	/* Sources collection tools. */
	ModuleSourceFunction downloader;
	ModuleSourceFunction extractor;

	/* Construction tools. */
	ModuleFunction configure;
	ModuleFunction build;
	ModuleFunction install;

	/* Packages building. */
	ModuleFunction assembler;

	ModuleOnExitFunction on_exit;
} Module;

Module** load_modules();
void modules_on_exit(Configuration*, Module**, int);

#endif

