
#ifndef _H_RECIPE
#define _H_RECIPE

#include <mpkgmk_private.h>

RecipeElement* recipe_alist_get(RecipeAList *alist, char *key);

/*
 * Testing, temporary stuff.
 */

RecipeElement* test_recipe();
RecipeElement* load_recipe(char *filename);

Source** get_sources(RecipeElement *recipe);

#endif

