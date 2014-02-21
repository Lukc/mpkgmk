#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

#include "ui.h"
#include "modules.h"

typedef void module_loader(Module*);

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

	modules = (Module**) NULL;
	count = 0;

	/* FIXME: load them all, damnit */
	/*while (something) {*/
		handle = dlopen("./src/modules/archive.so", RTLD_LAZY);
		if (handle) {
			load_module = (module_loader*) dlsym(handle, "load_module");

			if (load_module) {
				module = (Module*) malloc(sizeof(Module));
				(*load_module)(module);
				add_module(&modules, module, &count);
			} else {
				error(dlerror());
				error("  Module not loaded.");
			}

			dlclose(handle);
		} else {
			error(dlerror());
			error("  Module not loaded.");
		}
	/*}*/

	return modules;
}

