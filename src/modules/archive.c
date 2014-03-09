#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#include "../ui.c"
#include <mpkgmk_private.h>

int
mpkgmk_extractor(Source *source, Configuration *configuration) {
	char *filename, *filename2;
	struct archive *a;
	struct archive_entry *e;

	/* FIXME: check the source entry has a valid extension */
	filename = (char*) malloc(
		sizeof(char) * (
			strlen(configuration->sources_directory)
			+ strlen(source->filename)
			+ 2
	));
	sprintf(filename, "%s/%s", configuration->sources_directory, source->filename);

	/* FIXME: This is shit… (but probably works) */
	if (
		strlen(filename) < 8 || (
			strcmp(filename + sizeof(char) *
				(strlen(filename) - 7), ".tar.gz") &&
			strcmp(filename + sizeof(char) *
				(strlen(filename) - 7), ".tar.xz") &&
			strcmp(filename + sizeof(char) *
				(strlen(filename) - 8), ".tar.bz2")
		)
	) {
		return MODULE_USELESS;
	}

	a = archive_read_new();
	archive_read_support_filter_all(a);
	archive_read_support_format_all(a);
	archive_read_open_filename(
		a, filename, 1
	);

	info("%s", filename);

	free(filename);

	e = NULL;

	while (archive_read_next_header(a, &e) == ARCHIVE_OK) {
		filename2 = (char *) archive_entry_pathname(e);
		filename = (char *) malloc(
			sizeof(char) * (
				strlen(filename2) +
				strlen(configuration->working_directory) + 2
			)
		);
		sprintf(
			filename,
			"%s/%s", configuration->working_directory, filename2
		);

		archive_entry_set_pathname(e, filename);

		archive_read_extract(a, e, 0);
	}

	archive_read_free(a);

	return MODULE_SUCCEEDED;
}

