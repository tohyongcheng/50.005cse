#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

void function_to_time() {
   int i,j;
   double s=0;
   
   for (j=0;j<10;j++){
   	for (i=0;i<100000000;i++){
	   s+= rand()/(double)RAND_MAX;
   	} 
   }
   
}

int main(void) { 
   double clockticks, cticks;
   clock_t tcend, tcstart;
   struct tms tmend, tmstart;

   if ((clockticks = (double) sysconf(_SC_CLK_TCK)) == -1) {
      perror("Failed to determine clock ticks per second");
      return 1;
   }
   printf("The number of ticks per second is %f\n", clockticks);
   
   
   tcstart = times(&tmstart);
   function_to_time();
   tcend = times(&tmend);
   
   float timeTakenForCPU = ((tmend.tms_utime + tmend.tms_stime)-(tmstart.tms_utime + tmstart.tms_stime)) / clockticks;
   double timeTakenForProcess = (tcend - tcstart)/clockticks;
   printf("Total CPU time for operation is %f seconds\n",  timeTakenForCPU); 
   
   printf("Fraction of CPU time used is %f\n", timeTakenForCPU/timeTakenForProcess);
   return 0;
} 
