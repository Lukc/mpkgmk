
#ifndef _H_DOWNLOAD
#define _H_DOWNLOAD

#include "configuration.h"
#include "recipe.h"
#include "modules.h"

void download(RecipeElement *recipe, Module **modules, Configuration *configuration, Source **sources);

#endif

