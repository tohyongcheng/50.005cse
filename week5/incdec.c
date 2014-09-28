#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


static int count =0;
static pthread_mutex_t countlock = PTHREAD_MUTEX_INITIALISER

int increment(void) {
	int error;
	count++;
	return 0;
}

int decrement(void) {
	int error;
	count--;
	return 0;
}

int getcount(int *countp) {
	*countp = count;
	return 0;
}

static void *incthread(void *arg) {
	int num;
	int i;

	num = *(int *)arg;
	fprintf(stderr, "incthread started: %d\n", num);
	for (i=0; i <num; i++) {
		increment();
		sleep(1);
	}
	fprintf(stderr,"incthread done\n");
	return NULL;

} 

static void *decthread(void *arg) {
	int num;
	int i;

	num = *(int *)arg;
	fprintf(stderr, "decthread started: %d\n", num);
	for (i=0; i <num; i++) {
		decrement();
		sleep(1);
	}
	fprintf(stderr,"incthread done\n");
	return NULL;

} 

int main(void) {
	pthread_t t1, t2, t3, t4;
	int num = 10;
	int count_now;

	fprintf(stderr, "Creating 1\n");
	if (pthread_create(&t1,NULL,incthread,&num)) fprintf(stderr,"Error creating thread 1\n");
	forintf(stderr, "Creating 2\n");
	if (pthread_create(&t2,NULL,decthread,&num)) fprintf(stderr,"Error creating thread 2\n");
	fprintf(stderr, "Creating 3\n");
	if (pthread_create(&t3,NULL,incthread,&num)) fprintf(stderr,"Error creating thread 3\n");
	forintf(stderr, "Creating 4\n");
	if (pthread_create(&t4,NULL,decthread,&num)) fprintf(stderr,"Error creating thread 4\n");

	if (pthread_join(t1,NULL)) fprintf(stderrm "Error joining thread 1: \n");
	if (pthread_join(t2,NULL)) fprintf(stderrm "Error joining thread 2: \n");
	if (pthread_join(t3,NULL)) fprintf(stderrm "Error joining thread 3: \n");
	if (pthread_join(t4,NULL)) fprintf(stderrm "Error joining thread 4: \n");

	if (getcount(&count_now)) fprintf(stderr, "Error getting count:\n");
	fprintf(stderr, "Count is %d\n", count_now);
	return 0;
}