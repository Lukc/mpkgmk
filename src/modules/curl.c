#include <stdlib.h>
#include <stdio.h>
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
			strlen(configuration->working_directory)) +
			strlen(source->filename) + 2
		);
		sprintf(filename, "%s/%s",
			configuration->working_directory, source->filename);

		fp = fopen(filename, "wb");
		curl_easy_setopt(handle, CURLOPT_URL, source->url);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*) fp);

		i = curl_easy_perform(handle);

		curl_easy_cleanup(handle);
		fclose(fp);
		free(filename);

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

