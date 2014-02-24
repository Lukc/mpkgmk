#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#include "ui.h"
#include "modules.h"
#include "configuration.h"

static int
is_a_module_name(char *string) {
	int l;

	l = strlen(string);

	return !strcmp(string + l - 3, ".so");
}

static void
add_module(Module ***modules, Module *module, int *count) {
	*count = (*count) + 1;

	*modules = (Module**) realloc(*modules, sizeof(Module*) * (*count));
	(*modules)[*count-1] = module;
}

Module**
load_modules(Configuration *configuration) {
	Module **modules, *module;
	void *handle;
	int count;
	char *filename;
	struct dirent *entry;
	DIR *directory;
	ModuleOnLoadFunction *on_load;

	modules = (Module**) NULL;
	count = 0;

	directory = opendir(LIBDIR);
	if (!directory) {
		error("Could not open " LIBDIR ". Are you sure this directory exists?");

		return (Module**) NULL;
	}

	while ( (entry = readdir(directory)) ) {
		if (is_a_module_name(entry->d_name)) {
			filename = strdup(LIBDIR);
			filename = (char*) realloc(filename, sizeof(LIBDIR) + sizeof(entry->d_name) + 2);
			strcat(filename, "/");
			strcat(filename, entry->d_name);

			handle = dlopen(filename, RTLD_LAZY);
			if (handle) {
				module = (Module*) malloc(sizeof(Module));

				module->name = entry->d_name;

				module->downloader =  (ModuleSourceFunction*) dlsym(handle, "mpkgmk_downloader");
				module->extractor =   (ModuleSourceFunction*) dlsym(handle, "mpkgmk_extractor");

				module->configure =   (ModuleFunction*) dlsym(handle, "configure");
				module->build =       (ModuleFunction*) dlsym(handle, "build");
				module->install =     (ModuleFunction*) dlsym(handle, "install");

				module->assembler =   (ModuleFunction*) dlsym(handle, "assembler");

				add_module(&modules, module, &count);

				on_load = (ModuleOnLoadFunction*) dlsym(handle, "mpkgmk_on_load");
				if (on_load) {
					(*on_load)(configuration);
				}

#				ifdef DEBUG
					debug("[module loaded] %s", filename);
#				endif

				/*dlclose(handle); Uh, FIXME: Should be called, but way later.*/
			} else {
				error(dlerror());
				error("  Module not loaded.");
			}
			free(filename);
		}
	}

	add_module(&modules, NULL, &count);

	return modules;
}

