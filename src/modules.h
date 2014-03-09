
#ifndef _H_MODULES
#define _H_MODULES

#include "recipe.h"
#include "configuration.h"

Module** load_modules();
void modules_on_exit(Configuration*, Module**, int);

#endif

