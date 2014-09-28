#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
// #define ITERATION 10
#define MILLION 1000000

void function_to_time() {
   int i;
   double s=0;
   for (i=0;i<100000000;i++){
	   s+= rand()/(double)RAND_MAX;
   } 
}

int main(void) {

	// time_t start_time, end_time;
	// time_t elapsed_time;
	struct timeval start_time, end_time;
	long elapsed_time;


	if (gettimeofday(&start_time,0)) {
		fprintf(stdout,"Failed to get start time.\n");
		return 1;
	}

	int i =0;
	// for (i=0;i<ITERATION;i++)
  	function_to_time();
  if (gettimeofday(&end_time,0)) {
		fprintf(stdout,"Failed to get end time.\n");
		return 1;
  }

  // elapsed_time = end_time - start_time; 
  elapsed_time = MILLION*(end_time.tv_sec - start_time.tv_sec) + end_time.tv_usec - start_time.tv_usec;

  printf("The time taken is: %ld us \n",elapsed_time);

  return 0;
}
