
/*
 * FIXME: Those things should at least do something. At least create
 *        a file with their name and check for the existence of a file
 *        of the name of the previous module, or something.
 */

int
test_downloader(Source *source, Configuration *configuration) {
	char *protocol;
	protocol = source->protocol;

	if (!strcmp(protocol, "test")) {
		info("Test pseudo-download module: [%s] %s from %s.", protocol, source->filename, source->url);

		return MODULE_SUCCEEDED;
	}

	return MODULE_USELESS;
}
int
test_extractor(Source *source, Configuration *configuration) {
	char *filename;

	filename = (char*) malloc(
		sizeof(char) * (
			strlen(configuration->sources_directory)
			+ strlen(source->filename)
			+ 2
	));
	sprintf(filename, "%s/%s", configuration->sources_directory, source->filename);
	if (!strcmp(source->protocol, "test")) {
		info("Test pseudo-extraction module: %s.", filename);

		return MODULE_SUCCEEDED;
	}

	return MODULE_USELESS;
}

int
test_configure(RecipeElement *recipe, Configuration *configuration) {
	info("Test configure.");

	return MODULE_SUCCEEDED;
}

int
test_build(RecipeElement *recipe, Configuration *configuration) {
	info("Test build.");

	return MODULE_SUCCEEDED;
}
int
test_install(RecipeElement *recipe, Configuration *configuration) {
	info("Test install.");

	return MODULE_SUCCEEDED;
}

int
test_assembler(RecipeElement *recipe, Configuration *configuration) {
	if (!strcmp(configuration->assembler, "test")) {
		info("Test assembler.");

		return MODULE_SUCCEEDED;
	} else {
		return MODULE_USELESS;
	}
}

void
add_test_module(Module ***modules, int *count) {
	Module *module;

	module = (Module*) malloc(sizeof(Module));
	module->name = "c-test";
	module->downloader = test_downloader;
	module->extractor = test_extractor;
	module->configure = test_configure;
	module->build = test_build;
	module->install = test_install;
	module->assembler = test_assembler;

	add_module(modules, module, count);
}

