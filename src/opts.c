#include <stdlib.h>
#include <popt.h>
#include <mpkgmk_private.h>

#include "error.h"
#include "opts.h"

void
parse_options(int argc, char *argv[], Configuration *configuration) {
	poptContext context;
	char c;
	struct poptOption options[] = {
		POPT_AUTOHELP
		{ NULL, 0, 0, NULL, 0, NULL, NULL}
	};

	context = poptGetContext(NULL, argc, (const char**) argv, options, 0);
	poptSetOtherOptionHelp(context, "[options] [packages]");

	while ((c = poptGetNextOpt(context)) >= 0) {
		switch (c) {
			case 't':
				printf("test?\n");
				break;
			default:
				printf(" >> %c\n", c);
		}
	}

	if (c < -1) {
		error("%s", poptStrerror(c));

		poptFreeContext(context);

		/* FIXME: Dedicated error in error.h */
		exit(ERROR_CLI_ERROR);
	}

	poptFreeContext(context);
}

