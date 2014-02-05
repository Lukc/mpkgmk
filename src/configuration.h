
#ifndef _H_CONFIGURATION
#define _H_CONFIGURATION

#include "recipe.h"

typedef struct Configuration {
	int download;

	char *sources_directory;
	char *working_directory;
	char *assembler;
} Configuration;

Configuration* load_configuration(RecipeElement *recipe);

#endif

