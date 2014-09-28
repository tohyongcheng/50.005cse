#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>



int main(void) {

	pid_t child_pid;
	int i, n =3;
	int iWait;

	for (i=0;i<n;i++) {
		child_pid = fork();
		if (child_pid != 0) {
			break;
		}
	}

	for (;;) {
		iWait = wait(NULL);
		if ((iWait == -1 ) &&  (errno!= EINTR)) {
			break;
		}
	}

	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",i,(long)getpid(), (long)getppid(),(long)child_pid);
}