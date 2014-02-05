#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ui.h"
#include "modules.h"

static void
add_module(Module ***modules, Module *module, int *count) {
	*count = (*count) + 1;

	*modules = (Module**) realloc(*modules, sizeof(Module*) * (*count + 1));
	(*modules)[*count-1] = module;

	/* FIXME: Somewhat wrong. */
	(*modules)[*count] = (Module*) NULL;
}

#include "modules/test.c"
#include "modules/archive.c"

Module**
load_modules() {
	Module **modules;
	int count;

	modules = (Module**) NULL;
	count = 0;

	add_archive_module(&modules, &count);
	add_test_module(&modules, &count);

	return modules;
}

