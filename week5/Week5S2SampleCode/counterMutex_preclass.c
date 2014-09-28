#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static int count = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_T_INITIALIZER;


int increment(void) {                  /* increment the counter */
   int error;
    
    error = pthread_mutex_lock(&mut);
    if (error!=0) {
        return error;
    }
   
   count++;
   return pthread_mutex_unlock(&mut);
}

int decrement(void) {                 /* decrement the counter */
   int error;
    
    error = pthread_mutex_lock(&mut);
    if (error!=0) {
        return error;
    }
    count--;
    return pthread_mutex_unlock(&mut);
}

int getcount(int *countp) {           /* retrieve the counter */
   int error; 
    error = pthread_mutex_lock(&mut);
    if (error!=0) {
        return error;
    }
   *countp = count;  
   return pthread_mutex_unlock(&mut);
} 

static void *incthread(void *arg) {
   int num;
   int i;
  
   num = *(int *)arg;
   fprintf(stderr,"incthread started: %d\n",num);
   for (i=0;i<num;i++) {
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
   fprintf(stderr,"decthread started: %d\n",num);
   for (i=0;i<num;i++) {
      decrement();
      sleep(1);
     
   }
   fprintf(stderr,"decthread done\n");
   return NULL;
}

int main(void) {
    


    pthread_t t1,t2,t3,t4;
    int num = 10;
    int count_now;

    fprintf(stderr,"Creating 1\n");
    if (pthread_create(&t1,NULL,incthread,&num))
       fprintf(stderr,"Error creating thread 1\n");
    fprintf(stderr,"Creating 2\n");
    if (pthread_create(&t2,NULL,decthread,&num))
       fprintf(stderr,"Error creating thread 2\n");
    fprintf(stderr,"Creating 3\n");
    if (pthread_create(&t3,NULL,incthread,&num))
       fprintf(stderr,"Error creating thread 3:\n");
    fprintf(stderr,"Creating 4\n");
    if (pthread_create(&t4,NULL,decthread,&num))
       fprintf(stderr,"Error creating thread 4:\n");
    if (pthread_join(t1,NULL))
       fprintf(stderr,"Error joining thread 1:\n");
    if (pthread_join(t2,NULL))
       fprintf(stderr,"Error joining thread 2:\n");
    if (pthread_join(t3,NULL))
       fprintf(stderr,"Error joining thread 3:\n");
    if (pthread_join(t4,NULL))
       fprintf(stderr,"Error joining thread 4:\n");
    if (getcount(&count_now))
       fprintf(stderr,"Error getting count:\n");
    fprintf(stderr,"Count is %d\n",count_now);
    return 0;
		
}