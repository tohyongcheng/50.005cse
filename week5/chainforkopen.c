#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
#define CREATE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define BUFSIZE 1024

/**
* Question 1:
* All the first statements referring to process id is printed first, followed by the 2nd statements. 
*/

/**
* Question 2:
* We see only the last process's statements being printed in output file. 
* The first program printed for all the processes. 
* 
*/


/**
* Question 3:
* The last process (in this case 10) is always executed last. The contents
* of the process keep changing. An extra character 'p' or an integer replaces the
* last character of the first statement.
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

	sprintf(buf, "i:%d process:%ld", i, (long)getpid());
	write(fd, buf, strlen(buf));

	sleep(1);

	sprintf(buf, "parent:%ld child:%ld\n", (long) getppid(), (long) child_pid);
	write(fd, buf, strlen(buf));
	return 0;
}