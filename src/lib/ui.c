#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/**
 * TODO:
 *   enable_colors(bool) or something
 */

void
mpkgmk_info(const char *format, ...) {
	va_list l;
	va_start(l, format);

	printf("-- ");
	vfprintf(stdout, format, l);
	printf("\n");

	va_end(l);
}

#ifdef DEBUG
void
mpkgmk_debug(const char *format, ...) {
	va_list l;
	va_start(l, format);

	fprintf(stderr, ":: ");
	vfprintf(stderr, format, l);
	fprintf(stderr, "\n");

	va_end(l);
}
#endif

void
mpkgmk_warning(const char *format, ...) {
	va_list l;
	va_start(l, format);

	fprintf(stderr, "-- ");
	vfprintf(stderr, format, l);
	fprintf(stderr, "\n");

	va_end(l);
}

void
mpkgmk_error(const char *format, ...) {
	va_list l;
	va_start(l, format);

	fprintf(stderr, "-- ");
	vfprintf(stderr, format, l);
	fprintf(stderr, "\n");

	va_end(l);
}

