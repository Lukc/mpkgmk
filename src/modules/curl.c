#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "../ui.h"
#include "../modules.h"

int
module_curl_downloader(Source *source, Configuration *configuration) {
	int i;
	CURL *handle;

	info("inside");

	i = (
		!strcmp("http", source->protocol) ||
		!strcmp("https", source->protocol) ||
		!strcmp("ftp", source->protocol)
	);

	if (i) {
		handle = curl_easy_init();

		curl_easy_setopt(handle, CURLOPT_URL, source->url);

		i = curl_easy_perform(handle);

		curl_easy_cleanup(handle);

		if (i == CURLE_OK)
			return MODULE_SUCCEEDED;
		else {
			error("Download of %s failed: %s.",
				source->url, curl_easy_strerror(i));

			return MODULE_FAILED;
		}
	} else
		return MODULE_USELESS;
}

void
load_module(Module *module) {
	module->name = "curl";
	module->downloader = module_curl_downloader;
	module->extractor = NULL;
	module->configure = NULL;
	module->build = NULL;
	module->install = NULL;
	module->assembler = NULL;
}

