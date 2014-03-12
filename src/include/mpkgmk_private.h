
/*
 * This file might be removed, at some point.
 */

#ifndef _H_MPKGMK
#define _H_MPKGMK

#include <mpkgmk.h>

#define Configuration         MpkgmkConfiguration

#define Package               MpkgmkPackage

#define RecipeList            MpkgmkRecipeList
#define RecipeAList           MpkgmkRecipeAList
#define Version               MpkgmkVersion
#define Source                MpkgmkSource
#define RecipeElement         MpkgmkRecipe

#define RECIPE_INTEGER        MPKGMK_RECIPE_INTEGER
#define RECIPE_STRING         MPKGMK_RECIPE_STRING
#define RECIPE_BOOL           MPKGMK_RECIPE_BOOL
#define RECIPE_LIST           MPKGMK_RECIPE_LIST
#define RECIPE_ALIST          MPKGMK_RECIPE_ALIST
#define RECIPE_VERSION        MPKGMK_RECIPE_VERSION
#define RECIPE_SOURCE         MPKGMK_RECIPE_SOURCE

#define ModuleFunction        MpkgmkModuleFunction
#define ModuleSourceFunction  MpkgmkModuleSourceFunction
#define ModuleAssemblerFunction MpkgmkModuleAssemblerFunction
#define ModuleOnLoadFunction  MpkgmkModuleOnLoadFunction
#define ModuleOnExitFunction  MpkgmkModuleOnExitFunction
#define Module                MpkgmkModule

#define shell                 mpkgmk_shell
#define info                  mpkgmk_info
#define warning               mpkgmk_warning
#define error                 mpkgmk_error

#endif

