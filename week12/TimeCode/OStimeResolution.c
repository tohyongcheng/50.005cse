#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#define MILLION 1000000L



int main(void) {
   long timedif;
   struct timeval tpend;
   struct timeval tpstart;

   if (gettimeofday(&tpstart, NULL)) {
      fprintf(stderr, "Failed to get start time\n");
      return 1;
   }
   
   do{
   	 gettimeofday(&tpend, NULL);
   }while((tpstart.tv_usec==tpend.tv_usec) && (tpstart.tv_sec==tpend.tv_sec));
   
   timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
                      tpend.tv_usec - tpstart.tv_usec;
   printf("The OS resolution %ld microseconds\n", timedif);
   return 0;
}
