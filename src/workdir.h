
#ifndef _H_WORKDIR
#define _H_WORKDIR

#include "recipe.h"
#include "configuration.h"

char* get_work_dir(RecipeElement *recipe, Configuration *configuration);
void create_work_dir(char *work_dir);
void clean_work_dir(char *work_dir);

#endif

