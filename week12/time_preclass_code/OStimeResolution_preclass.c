#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#define MILLION 1000000L

int main(void) {
	long timedif;
	struct timeval tpend;
	struct timeval tpstart;

	gettimeofday(&tpstart, NULL);
	while(true) {
		gettimeofday(&tpend, NULL);
		if (tpend.tv_usec != tpstart.tv_usec ) break;
	}
	timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
	printf("The OS resolution is %ld microseconds\n", timedif);
	return 0;
}
