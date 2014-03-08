#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

#include "../ui.c"
#include "../modules.h"


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}


int
mpkgmk_downloader(Source *source, Configuration *configuration) {
	int i;
	CURL *handle;
	FILE *fp;
	char *filename;

	i = (
		!strcmp("http", source->protocol) ||
		!strcmp("https", source->protocol) ||
		!strcmp("ftp", source->protocol)
	);

	if (i) {
		handle = curl_easy_init();

		filename = (char*) malloc(sizeof(char) * (
			strlen(configuration->sources_directory)) +
			strlen(source->filename) + 2
		);
		sprintf(filename, "%s/%s",
			configuration->sources_directory, source->filename);

		fp = fopen(filename, "w+b");
		if (! fp) {
			error("Could not open file: %s", filename);
			return MODULE_FAILED;
		}
		curl_easy_setopt(handle, CURLOPT_URL, source->url);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*) fp);

		i = curl_easy_perform(handle);

		curl_easy_cleanup(handle);
		fclose(fp);

		if (i == CURLE_OK) {
			free(filename);

			return MODULE_SUCCEEDED;
		} else {
			error("Download of %s failed: %s.",
				source->url, curl_easy_strerror(i));

			unlink(filename);
			free(filename);

			return MODULE_FAILED;
		}
	} else
		return MODULE_USELESS;
}

