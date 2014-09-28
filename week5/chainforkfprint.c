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

Question 7

The program behaves well as expected. 

i:0 process:42853 parent:41840 child:42854
i:1 process:42854 parent:42853 child:42855
i:3 process:42856 parent:42855 child:42857
i:2 process:42855 parent:42854 child:42856
i:4 process:42857 parent:42856 child:42858
i:5 process:42858 parent:42857 child:42859
i:7 process:42860 parent:42859 child:42861
i:6 process:42859 parent:1 child:42860
i:8 process:42861 parent:1 child:42862
i:9 process:42862 parent:42861 child:42863
i:10 process:42863 parent:42862 child:0

*/


int main(int argc, char* argv[]) {
	pid_t child_pid = 0;
	int i,n;
	FILE * fp;
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

	fp = fopen(argv[2], "a");
	if (fp == NULL ) {
		perror("Failed to open file");
		return 1;
	}

	//Check for error
	if (child_pid == -1) {
		perror("Failed to fork");
		return 1;
	}

	fprintf(fp, "i:%d process:%ld parent:%ld child:%ld\n", i, (long)getpid(), (long) getppid(), (long) child_pid);

	return 0;
}