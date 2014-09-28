#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#define MAX_SIZE 65536

int SIZE;
int numArray[MAX_SIZE] = {};
int result[MAX_SIZE] = {};
int NUMBER_OF_THREADS;

void *sorter(void *params);
void *merger(void *params);

typedef struct{
	int from_index;
	int to_index;
} parameters;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s number_of_threads\n", argv[0]);
		return 1;
	} 

	NUMBER_OF_THREADS = atoi(argv[1]);

	clock_t tstart;
	clock_t tend;
	int i = 0;
	int j = 0;
	FILE *infile;
	parameters *data[NUMBER_OF_THREADS];
	pthread_t workers[NUMBER_OF_THREADS+1]; // +1 for merging thread

	// Take data from input file
	infile = fopen("./input2.txt", "r");
	while(!feof(infile)) {
		fscanf(infile, "%d", &numArray[i]);
		i++;
	}
	fclose(infile);

	SIZE = i - 1;
	printf("Total number of integers is %d\n", i-1);

	//copy to a new array called result
	for (i=0; i< SIZE; i++) {
		result[i] = numArray[i];
	}

	int interval = (SIZE/NUMBER_OF_THREADS);
	int arraySpaces[NUMBER_OF_THREADS];

	for (i =0; i<NUMBER_OF_THREADS; i++) {
		arraySpaces[i] = interval;
	}
	
	int leftover = SIZE - interval * NUMBER_OF_THREADS;
	i = 0;
	while(leftover > 0) {
		arraySpaces[i]++;		
		leftover--;
		i++;
	}

	int start = 0;
	for(i=0;i<NUMBER_OF_THREADS;i++) {
		data[i] = (parameters *) malloc(sizeof(parameters));
		data[i]->from_index = start;
		//check if is at the end of array
		data[i]->to_index = start+arraySpaces[i] - 1;
		start += arraySpaces[i];
		printf("%ld\t%d\t%d\n", sizeof(parameters), data[i]->from_index, data[i]->to_index);
	}

	//Do sort
	tstart = clock(); //start timing

	for(i=0;i<NUMBER_OF_THREADS;i++) {
		pthread_create(&workers[i], 0, sorter, data[i]);
		// printf("%ld\t%d\t%d\n", sizeof(parameters), data[i]->from_index, data[i]->to_index);
	}

	for(i=0;i<NUMBER_OF_THREADS;i++){
		pthread_join(workers[i],NULL);
	}

	// Start Merge
	pthread_create(&workers[NUMBER_OF_THREADS], 0, merger, data);
	pthread_join(workers[NUMBER_OF_THREADS],NULL);


	//End sort
	tend = clock();
	

	//Print all numbers after sorted in each subarray
	for(i=0;i<SIZE;i++) {
		printf("%d ",result[i]);
	}
	printf("\nIt took me %f ms to sort %d numbers using %d threads.\n", 
		(((float)tend-tstart)/CLOCKS_PER_SEC*1000), (int) i, NUMBER_OF_THREADS);
	
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
	parameters** data = (parameters**) params;
	int cResult[MAX_SIZE];
	int min;
	int minPosition;
	
	int index[NUMBER_OF_THREADS];
	int end[NUMBER_OF_THREADS];
	
	int i;
	for (i=0; i<NUMBER_OF_THREADS;i++){
		index[i] = data[i]->from_index;
		end[i] = data[i]->to_index;
	}

	int pos = 0;
	int j;
	int temp;
	while(true){
		min = INT_MAX;
		minPosition = -1;
		
		for (j=0; j<NUMBER_OF_THREADS; j++) {
			temp = index[j];
			if ((temp <= end[j]) && (result[temp] < min)) {
				min = result[(index[j])];
				minPosition = j;
			}
		}
		
		if(minPosition == -1) {
			break;
		}

		cResult[pos] = min;
		pos++;
		index[minPosition] += index[j]+1;
		
	}

	for(i=0; i<SIZE;i++) {
		result[i] = cResult[i];
	}

	
}