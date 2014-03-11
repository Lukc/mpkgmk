
#ifndef _H_MPKGMK_PUBLIC
#define _H_MPKGMK_PUBLIC

/*
 * RECIPE AND RECIPE TYPES
 */

typedef struct MpkgmkRecipeList {
	struct MpkgmkRecipe *element;
	struct MpkgmkRecipeList *next;
} MpkgmkRecipeList;

typedef struct MpkgmkRecipeAList {
	char *key;
	struct MpkgmkRecipe *element;
	struct MpkgmkRecipeAList *next;
} MpkgmkRecipeAList;

typedef struct MpkgmkVersion {
	/* Integer or string. */
	int type;

	union {
		int *integer;
		char *string;
	} value;

	struct MpkgmkVersion *next;
} MpkgmkVersion;

typedef struct MpkgmkSource {
	char *url;
	char *protocol;
	char *filename;
} MpkgmkSource;

enum MPKGMK_RECIPE_TYPES {
	/* MPKGMK_Generic types. */
	MPKGMK_RECIPE_INTEGER, MPKGMK_RECIPE_STRING, MPKGMK_RECIPE_BOOL,
	MPKGMK_RECIPE_LIST, MPKGMK_RECIPE_ALIST,

	/* MPKGMK_Custom types. */
	RECIPE_VERSION, MPKGMK_RECIPE_SOURCE
};

typedef struct MpkgmkRecipe {
	int type;
	union {
		int *integer; /* Might be reused for bools. */
		struct MpkgmkRecipeList *list;
		struct MpkgmkRecipeAList *alist;
		char *string;
		MpkgmkVersion *Version;
	} data;
} MpkgmkRecipe;

/*
 * CONFIGURATION
 */

typedef struct MpkgmkConfiguration {
	int download;

	char *sources_directory;
	char *working_directory;
	char *packages_directory;
	char *assembler;
} MpkgmkConfiguration;

/*
 * MODULES
 */

#define MODULE_FAILED -1
#define MODULE_USELESS 0
#define MODULE_SUCCEEDED 1

typedef int (*MpkgmkModuleFunction)(MpkgmkRecipe*, MpkgmkConfiguration*);
typedef int (*MpkgmkModuleSourceFunction)(MpkgmkSource*, MpkgmkConfiguration*);
typedef int (*MpkgmkModuleOnLoadFunction)(MpkgmkConfiguration*);
typedef int (*MpkgmkModuleOnExitFunction)(MpkgmkConfiguration*, int);

typedef struct MpkgmkModule {
	char *name; /* For debug and info messages and assimilated */

	/* Sources collection tools. */
	MpkgmkModuleSourceFunction downloader;
	MpkgmkModuleSourceFunction extractor;

	/* Construction tools. */
	MpkgmkModuleFunction configure;
	MpkgmkModuleFunction build;
	MpkgmkModuleFunction install;

	/* Packages building. */
	MpkgmkModuleFunction assembler;

	MpkgmkModuleOnExitFunction on_exit;
} MpkgmkModule;

/*
 * Provided API
 */

int mpkgmk_shell(char*);

void mpkgmk_info(char*, ...);
void mpkgmk_warning(char*, ...);
void mpkgmk_error(char*, ...);

#endif

