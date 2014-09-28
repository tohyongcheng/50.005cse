#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#define MILLION 1000000L

void function_to_time() {
   int i;
   double s=0;
   for (i=0;i<100000000;i++){
	   s+= rand()/(double)RAND_MAX;
   } 
}

int main(void) {
   long timedif;
   struct timeval tpend;
   struct timeval tpstart;

   if (gettimeofday(&tpstart, NULL)) {
      fprintf(stderr, "Failed to get start time\n");
      return 1;
   }
   function_to_time();                              /* timed code goes here */
   if (gettimeofday(&tpend, NULL)) {
      fprintf(stderr, "Failed to get end time\n");
      return 1;
   }
   timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
                      tpend.tv_usec - tpstart.tv_usec;
   printf("The function_to_time took %ld microseconds\n", timedif);
   return 0;
}
