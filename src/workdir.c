#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>

#include "workdir.h"

void
create_work_dir(char *work_dir) {
	mkdir(work_dir, 0644);
}

