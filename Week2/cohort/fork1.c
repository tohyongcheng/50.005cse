#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {

	pid_t child_pid;
	int x = 1;

	child_pid = fork();

	if (child_pid == 0) {
		printf ("I'm a child process: x=%d\n", x);
	} else if (child_pid > 0) {
		printf("I'm parent process: x=%d\n", x);
	}
}