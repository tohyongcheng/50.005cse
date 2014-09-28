#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


#define BUFSIZE 1024
#define FILE_PERMS (S_IRUSR|S_IWUSR|S_IRGRP |S_IROTH)
#define FILE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)

int main() {
	char buf[BUFSIZE];
	int fd;

	fd = open("b.txt", FILE_FLAGS, FILE_PERMS);
	if (fd != 0) {
		perror("Open failed");
		return 1;
	}
	sprintf(buf, "process:%ld ", (long)getpid() );
	write(fd, buf, strlen(buf));
	sprintf(buf,"parent:%ld\n", (long)getpid() );
	write(fd, buf, strlen(buf));

	close(fd);
	return 0;

}