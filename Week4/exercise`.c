#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80

int main() {
	int length, i, ct =0;
	char inputBuffer_l[MAX_LINE] = {NULL} ;
	char * comIn[MAX_LINE/2 +1]= {NULL};
	char* token;
	int idx = 0;
	pid_t child_pid;

	printf("Please type in a string: ");
	fflush(stdout);

	length=read(STDIN_FILENO, inputBuffer_l, MAX_LINE);
	printf("\nThe input is %s and its length is %d\n", inputBuffer_l, length);

	comIn[idx] = strtok(inputBuffer_l, " \n");
	while(comIn[idx] !=  NULL) {
		printf("%s %lu\t", comIn[idx], strlen(comIn[idx]));
		idx++;
		comIn[idx] = strtok(NULL, " \n");
	}

	child_pid = fork();
	if (child_pid == 0) {
		execvp(comIn[2],comIn);
	} else {
		wait(NULL);
	}

	
	return 0;
}

