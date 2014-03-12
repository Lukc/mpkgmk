#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include "path_max.h"
#include "ui.h"
#include "extraction.h"
#include "error.h"

void
extract(RecipeElement *recipe, Module **modules, Configuration *configuration, Source **sources) {
	int i, j, ret, was_extracted;
	char cwd[PATH_MAX];
	Module *module;

	if (!configuration->download || !sources)
		return;

	getcwd(cwd, PATH_MAX);

	chdir(configuration->sources_directory);

	i = 0;
	while (sources[i]) {
		j = 0;
		was_extracted = 0;
		while (modules[j]) {
			module = modules[j];

			if (module->extractor) {
				ret = module->extractor(sources[i], configuration);

				if (ret == MODULE_FAILED) {
					error("An error occured while trying to extract one of the sources of your package.");
					exit(ERROR_DOWNLOAD_FAILED);
				} else if (ret == MODULE_SUCCEEDED) {
					was_extracted = 1;
					break;
				}
			}

			j++;
		}

		if (!was_extracted) {
			/* FIXME: We should copy the files we could not extract. */
			error("No module could extract %s.", sources[i]->filename);
			exit(ERROR_DOWNLOAD_FAILED);
		}

		i++;
	}

	chdir(cwd);
}

