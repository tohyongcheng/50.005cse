#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


#define BUFSIZE 1024
#define FILE_PERMS (S_IRUSR|S_IWUSR|S_IRGRP |S_IROTH)
#define FILE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)

int main(int argc, char **argv) {
	int newfd; //new file descriptor

	if ((newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
		perror(argv[1]); //open failed
		exit(1);
	}

	printf("This goes to the standard output.\n");
	printf("Now the standard output will go to \"%s\".\n", argv[1]);
	dup2(newfd, 1);
	printf("This goes to the standard output too.\n");
	exit(0);

}