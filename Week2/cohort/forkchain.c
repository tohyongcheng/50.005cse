#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {

	pid_t child_pid;
	int i, n =3;

	for (i=0;i<n;i++) {
		child_pid = fork();
	}

	for (;;) {
		child_pid = wait(NULL);
		if (child_pid == -1) && (errno1 == EINTR) {
			break;
		}
	}

	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",i,(long)getpid(), (long)getppid(),(long)child_pid);
}