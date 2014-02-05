
#ifndef _H_RECIPE
#define _H_RECIPE

typedef struct RecipeList {
	struct RecipeElement *element;
	struct RecipeList *next;
} RecipeList;

typedef struct RecipeAList {
	char *key;
	struct RecipeElement *element;
	struct RecipeAList *next;
} RecipeAList;

typedef struct Version {
	/* Integer or string. */
	int type;

	union {
		int *integer;
		char *string;
	} value;

	struct Version *next;
} Version;

typedef struct Source {
	char *url;
	char *protocol;
	char *filename;
} Source;

enum RECIPE_TYPES {
	/* Generic types. */
	RECIPE_INTEGER, RECIPE_STRING, RECIPE_BOOL, RECIPE_LIST, RECIPE_ALIST,

	/* Custom types. */
	RECIPE_VERSION, RECIPE_SOURCE
};

typedef struct RecipeElement {
	int type;
	union {
		int *integer; /* Might be reused for bools. */
		struct RecipeList *list;
		struct RecipeAList *alist;
		char *string;
		Version *version;
	} data;
} RecipeElement;



RecipeElement* recipe_alist_get(RecipeAList *alist, char *key);

/*
 * Testing, temporary stuff.
 */

RecipeElement* test_recipe();
RecipeElement* load_recipe(char *filename);

Source** get_sources(RecipeElement *recipe);

#endif

