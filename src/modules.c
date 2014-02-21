#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#include "ui.h"
#include "modules.h"

typedef void module_loader(Module*);

static int
is_a_module_name(char *string) {
	int l;

	l = strlen(string);

	return !strcmp(string + l - 3, ".so");
}

static void
add_module(Module ***modules, Module *module, int *count) {
	*count = (*count) + 1;

	*modules = (Module**) realloc(*modules, sizeof(Module*) * (*count + 1));
	(*modules)[*count-1] = module;

	/* FIXME: Somewhat wrong. */
	(*modules)[*count] = (Module*) NULL;
}

Module**
load_modules() {
	Module **modules, *module;
	module_loader *load_module;
	void *handle;
	int count;
	char *filename;
	struct dirent *entry;
	DIR *directory;

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
				load_module = (module_loader*) dlsym(handle, "load_module");

				if (load_module) {
					module = (Module*) malloc(sizeof(Module));
					(*load_module)(module);
					add_module(&modules, module, &count);

#					ifdef DEBUG
						debug("[module loaded] %s", filename);
#					endif
				} else {
					error(dlerror());
					error("  Module not loaded.");
				}

				dlclose(handle);
			} else {
				error(dlerror());
				error("  Module not loaded.");
			}
			free(filename);
		}
	}

	return modules;
}

