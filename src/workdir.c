#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/stat.h>

#include "workdir.h"

void
create_work_dir(char *work_dir) {
	if (mkdir(work_dir, 0777) == -1 && errno != EEXIST)
		perror("mkdir(work_dir)");
}

