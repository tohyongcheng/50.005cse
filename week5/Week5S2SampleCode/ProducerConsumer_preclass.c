
/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */
#include <fcntl.h>


int const MAX=5;
int buffer[MAX];
int fill = 0;
int use =0;
int loops = 10;

sem_t *items;
sem_t *slots;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;


void put(int value){

	sem_wait(slots);
	pthread_mutex_lock(&mut);
	printf("fill buffer %d with %d by thread %ld\n",fill,value,(long)pthread_self());
		
	buffer[fill] = value;
	fill= (fill+1)%MAX;
	pthread_mutex_unlock(&mut);
	sem_post(items);
} 

int get(){
	sem_wait(items);
	pthread_mutex_lock(&mut);
	int tmp = buffer[use];
	
	printf("Access get by Thread %ld with index %d\n",(long)pthread_self(),use);
	
	use = (use+1)%MAX;
	pthread_mutex_unlock(&mut);
	sem_post(slots);
	return tmp;
}

void *producer(void *arg){
	int i;
	
	for (i=0;i<loops;i++){		
		
		put(i);
		
		
	}
	
	pthread_exit(0); /* exit thread */
}

void *consumer(void *arg){
	int i;
	
	for (i=0;i<loops;i++){
		
		
		int temp = get();
		
		
		printf("Thread %ld consumes %d\n",(long)pthread_self(),temp);
				
	}
	
	pthread_exit(0); /* exit thread */
}

int main()
{
  	slots = sem_open("/item", O_CREAT, 0644 ,1); 
  	items = sem_open("/slot", O_CREAT, 0644 ,MAX); 
    pthread_t pid1, pid2, cid1,cid2;
   	
 
                                                                  
    pthread_create(&pid1, NULL, producer, NULL);
	pthread_create(&pid2, NULL, producer, NULL);  
    pthread_create(&cid1, NULL, consumer, NULL);
	pthread_create(&cid2, NULL, consumer, NULL);  

    pthread_join(pid1, NULL); 
	pthread_join(pid2, NULL); 
    pthread_join(cid1, NULL);
    pthread_join(cid2, NULL); 
    
   
                 
    /* exit */  
    exit(0);
} /* main() */



