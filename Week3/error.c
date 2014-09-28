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
	fprintf(stdout, "a");
	fprintf(stderr, "a has been written \n");
	fprintf(stdout, "b");
	fprintf(stderr, "b has been written \n");
	fprintf(stdout, "\n");
	return 0;

}