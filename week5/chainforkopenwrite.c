#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
 



#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_APPEND )
#define CREATE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define BUFSIZE 1024


/**
* Question 6
* The program behaves as expected and outputs the statements in the write order.
*
*/


int main(int argc, char* argv[]) {
	pid_t child_pid = 0;
	int i,n;
	int fd;
	char buf[BUFSIZE];

	if (argc != 3) {
		fprintf(stderr, "Usage: %s processes filename\n", argv[0]);
		return 1;
	} 

	n = atoi(argv[1]);

	for (i = 0; i<n; i++) {
		child_pid = fork();
		if (child_pid)
			break;
	}

	fd = open(argv[2], CREATE_FLAGS, CREATE_PERMS);
	if (fd < 0 ) {
		perror("Failed to open file");
		return 1;
	}

	//Check for error
	if (child_pid == -1) {
		perror("Failed to fork");
		return 1;
	}

	sprintf(buf, "i:%d process:%ld parent:%ld child:%ld\n", i, (long)getpid(), (long) getppid(), (long) child_pid);
	lseek(fd, 0, SEEK_END );
	write(fd, buf, strlen(buf));

	return 0;
}