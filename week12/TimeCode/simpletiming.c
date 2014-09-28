#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void function_to_time() {
   int i;
   double s=0;
   for (i=0;i<100000000;i++){
	   s+= rand()/(double)RAND_MAX;
   } 
}

int main(void) {
   time_t tstart, tend;  

   tstart = time(NULL);
   function_to_time();
   tend = time(NULL);
   
   printf("function_to_time took %f seconds of elapsed time\n", 
           difftime(time(NULL), tstart)); 
   //printf("function_to_time took %ld seconds of elapsed time\n", 
   //        tend-tstart); 
   
   return 0;
}
