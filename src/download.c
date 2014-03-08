#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* FIXME: I have no idea what I’m doing. */
#ifndef PATH_MAX
#define PATH_MAX _PC_PATH_MAX
#endif

#include "ui.h"
#include "recipe.h"
#include "download.h"
#include "error.h"

void
download(RecipeElement *recipe, Module **modules, Configuration *configuration, Source **sources) {
	int i, j, ret, was_downloaded;
	char cwd[PATH_MAX];
	FILE *f;
	Module *module;

	if (!configuration->download || !sources)
		return;

	getcwd(cwd, PATH_MAX);

	chdir(configuration->sources_directory);

	i = 0;
	while (sources[i]) {
		j = 0;
		was_downloaded = 0;

		if ( (f = fopen(sources[j]->filename, "r")) ) {
			info("%s already downloaded.", sources[j]->filename);
			was_downloaded = 1;
			fclose(f);
		} else {
			while (modules[j]) {
				module = modules[j];

				if (module->downloader) {
					ret = module->downloader(sources[i], configuration);

					if (ret == MODULE_FAILED) {
						error("An error occured while trying to get one of the sources of your package.");
						exit(ERROR_DOWNLOAD_FAILED);
					} else if (ret == MODULE_SUCCEEDED) {
						was_downloaded = 1;
						break;
					}
				}

				j++;
			}
		}

		if (!was_downloaded) {
			error("No module could download %s+%s.", sources[i]->protocol, sources[i]->url);
			exit(ERROR_DOWNLOAD_FAILED);
		}

		i++;
	}

	chdir(cwd);
}

