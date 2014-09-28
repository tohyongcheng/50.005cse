#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int r, pipeFDs[2];
char message[512];
pid_t spawnpid;

// int main() {
// 	if (pipe(pipeFDs) == -1) {
// 		perror("Hull Breach: ");
// 		exit(1);
// 	}

// 	spawnpid = fork();
// 	switch (spawnpid)
// 	{
// 		case 0: // Child
// 			close(pipeFDs[0]); //close the input file descriptor
// 			write(pipeFDs[1], "hi parent, this is the child!", 41);
// 			printf("This is the child process \n");
// 			exit(0);
// 		default: //Parent
// 			close(pipeFDs[1]);
// 			r = read(pipeFDs[0],message, sizeof(message));
// 			if (r > 0) 
// 				printf("Message received from the child: %s \n",message);
// 			exit(0);
// 	}

// }

int main() {
	if (pipe(pipeFDs) == -1) {
		perror("Hull Breach: ");
		exit(1);
	}

	spawnpid = fork();
	switch (spawnpid)
	{
		case 0: // Child
			close(pipeFDs[1]);
			r = read(pipeFDs[0],message, sizeof(message));
			if (r > 0) 
				printf("Message received from the parent: %s \n",message);
			exit(0);
		default: //Parent
			

			close(pipeFDs[0]); //close the input file descriptor
			write(pipeFDs[1], "hi child, this is the parent!", 41);
			printf("This is the parent process \n");
			exit(0);
	}

}