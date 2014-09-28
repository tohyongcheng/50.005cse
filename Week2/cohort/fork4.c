#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {

	pid_t child_pid;
	int i, n =3;

	for (i=0;i<n;i++) {
		child_pid = fork();
	}

	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",i,(long)getpid(), (long)getppid(),(long)child_pid);
}