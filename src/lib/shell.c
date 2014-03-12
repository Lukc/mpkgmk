#include <unistd.h>
#include <stdio.h>
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
	system(str);
}

