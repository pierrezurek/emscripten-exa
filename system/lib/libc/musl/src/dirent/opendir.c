#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include "__dirent.h"
#include "syscall.h"

DIR *opendir(const char *name)
{
	int fd;
	DIR *dir;

	if ((fd = open(name, O_RDONLY|O_DIRECTORY|O_CLOEXEC)) < 0)
		return 0;
	if (!(dir = calloc(1, sizeof *dir))) {
#ifdef __EMSCRIPTEN__EXA
		__wasi_fd_close(fd);
#else
		__syscall(SYS_close, fd);
#endif
		return 0;
	}
	dir->fd = fd;
	return dir;
}
