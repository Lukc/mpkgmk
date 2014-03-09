#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

int
mpkgmk_shell(char *code) {
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) != 0) {
		return -1;
	}

	pid = fork();
	if (pid == 0) {
		close(pipefd[1]);

		dup2(pipefd[0], 0);
		execl("/bin/sh", "sh", NULL);
		return -2;
	} else if (pid == -1) {
		return -3;
	} else {
		int status;

		close(pipefd[0]);

		write(pipefd[1], "set -x -e\n", strlen("set -x -e\n"));
		write(pipefd[1], code, strlen(code));
		close(pipefd[1]);

		waitpid(pid, &status, 0);

		return status;
	}
}

