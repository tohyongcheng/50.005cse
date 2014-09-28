#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10
#define NUMBER_OF_THREADS 3

void *sorter(void *params);
void *merger(void *params);

int list[SIZE] = {7,12,19,3,18,4,2,6,15,8};
int result[SIZE];

typedef struct{
	int from_index;
	int to_index;
} parameters;

int main() {
	
	int i;

	for (i=0; i< SIZE; i++) {
		result[i] = list[i];
	}

	pthread_t workers[NUMBER_OF_THREADS];

	parameters *data = (parameters*) malloc (sizeof(parameters));
	data->from_index = 0;
	data->to_index = (SIZE/2) -1;
	pthread_create(&workers[0], 0, sorter, data);
	printf("%ld\t%d\t%d\n", sizeof(parameters), data->from_index, data->to_index);

	parameters *data2 = (parameters*) malloc (sizeof(parameters));
	data2->from_index = (SIZE/2);
	data2->to_index = SIZE-1;
	pthread_create(&workers[1], 0, sorter, data2);
	printf("%ld\t%d\t%d\n", sizeof(parameters), data2->from_index, data2->to_index);

	pthread_join(workers[0],NULL);
	pthread_join(workers[1],NULL);

	pthread_create(&workers[2],0,merger, NULL);
	pthread_join(workers[2],NULL);


	for (i=0;i<10;i++) {
		printf("%d\n", result[i]);
	}

	return 0;
}

void* sorter(void* params) {
	parameters* p = (parameters*) params; 
	int start = p->from_index;
	int end = p->to_index;
	int d;
	int t;
	//Insertion sort
	for (int c = start; c <= end; c++) {
		d = c;
		while(d > start && result[d] < result[d-1]) {
			t = result[d];
			result[d] = result[d-1];
			result[d-1] = t;
			d--;
		}
	}
}

void* merger(void* params) {
	int i =0;
	int j =SIZE/2;
	int pos = 0;
	int cResult[SIZE];

	while(i < SIZE/2 && j <SIZE ) {
		if (result[i] < result[j]) {
			cResult[pos] = result[i];
			i++;
			pos++;
		} else {
			cResult[pos] = result[j];
			j++;
			pos++;
		}
	}

	while(i<SIZE/2) {
		cResult[pos] = result[i];
		i++;
		pos++;
	}

	while(j<SIZE) {
		cResult[pos] = result[j];
		j++;
		pos++;
	}

	for(int i=0; i<SIZE;i++) {
		result[i] = cResult[i];
	}
	
}
