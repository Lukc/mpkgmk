#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mpkgmk_private.h>
#include "recipe.h"

/*
 * FIXME: Many assumptions are made about the structure of the recipe, but
 *        no checking has been done at this point. (this shouldn’t be done
 *        here anyway)
 */
Package*
recipe_to_packages(RecipeElement *recipe) {
	Package *packages;
	RecipeElement *e;

	packages = (Package*) malloc(sizeof(Package));

	e = recipe_alist_get(recipe->data.alist, "name");
	packages[0].name = strdup(e->data.string);

	e = recipe_alist_get(recipe->data.alist, "version");
	if (e->type == RECIPE_STRING)
		packages[0].version = strdup(e->data.string);
	else if (e->type == RECIPE_INTEGER) {
		/* FIXME: This sucks. */
		packages[0].version = (char*) malloc(sizeof(char) * 16);
		snprintf(packages[0].version, 16, "%i", e->data.integer);
	}

	e = recipe_alist_get(recipe->data.alist, "release");
	packages[0].release = e->data.integer;

	return packages;
}

