#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#define MILLION 1000000L
#define TIMER_MSG "Received Timer Interrupt\n"


/* ARGSUSED */
static void myhandler(int s) {
   char aster = '*';
   int errsave;
   errsave = errno;
   write(STDERR_FILENO, &aster, 1);
   errno = errsave;
}

static int setupinterrupt(void) {          /* set up myhandler for  SIGPROF */
   struct sigaction act;
   act.sa_handler = myhandler;
   act.sa_flags = 0;
   return (sigemptyset(&act.sa_mask) || sigaction(SIGALRM, &act, NULL));
}

static int setperiodic(double sec) {
  
   struct itimerval value;

  
   value.it_interval.tv_sec = (long)sec;
   value.it_interval.tv_usec = (sec - value.it_interval.tv_sec)*MILLION;
   if (value.it_interval.tv_usec >= MILLION) {
      value.it_interval.tv_sec++;
      value.it_interval.tv_usec -= MILLION;
   }
   value.it_value = value.it_interval;
   
   return (setitimer(ITIMER_REAL, &value, NULL));
}

int main(void) {
	
	double interval;
	
   if (setupinterrupt() == -1) {
      perror("Failed to setup SIGALRM handler");
      return 1;
   }
   
   printf("Enter timer interval in seconds (could be decimal numbers):");
   scanf("%lf",&interval);
   
   if (setperiodic(interval) == -1) {
      perror("Failed to setup periodic interrupt");
      return 1;
   }
   for ( ; ; )
      pause();
}
