#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


#define MAX_LINE 80

int main() {
	while(true) {
		int length, i, ct =0;
		char inputBuffer_l[MAX_LINE] = {};
		char * comIn[MAX_LINE/2 +1]= {};
		char* token;
		int idx = 0;
		pid_t child_pid;
		int exit;
		bool background = false;

		printf("Please type in a string: ");
		fflush(stdout);

		length=read(STDIN_FILENO, inputBuffer_l, MAX_LINE);
		// printf("\nThe input is %s and its length is %d\n", inputBuffer_l, length);
		if (length > 1) {
			exit = strncmp(inputBuffer_l, "exit\n", 5);
			if (exit == 0 ){
				return 0;
			}

			comIn[idx] = strtok(inputBuffer_l, " \n");


			while(comIn[idx] !=  NULL) {
				// printf("%s %lu\t", comIn[idx], strlen(comIn[idx]));
				idx = idx + 1;
				comIn[idx] = strtok(NULL, " \n");
			}

			if (strncmp(comIn[idx-1], "&", 1) == 0) {
				background = true;
				comIn[idx-1] = NULL;
			}

			// printf("The background is %d\n", background);
			fflush(stdout);

			child_pid = fork();
			if (child_pid < 0) {
				perror("Error forking!");
				return 1;
			}

			if (child_pid == 0) {
				execvp(comIn[0],comIn);
				return 0;
			} else if (child_pid > 0) {
				if (!background) {

					waitpid(child_pid, NULL,0);
				}
			}
		}
	}
}

