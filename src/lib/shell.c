#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

int
mpkgmk_shell(char *code) {
	char *str;
	int l;
	l = strlen("set -e -x;");
	str = strdup("set -e -x;");
	str = (char*) realloc(str, sizeof(char) * (
		l + strlen(code) + 1
	));

	strcpy(str+l, code);
	return system(str);
}

