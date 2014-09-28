#include <stdio.h>
#include <stdlib.h>

void manup_array(int *array[], int n) {
	int i;
	for (i=0; i < n; i++) {
		array[i] += 1;
	}
}

int main(int argc, char *argv[]) {
	int N;
	if (argc == 2) {
		N = atoi(argv[1]);
	} else {
		printf("Please enter N: ");
		scanf("%d", &N);
	}

	int A[N];
	int *B[N];
	int i;
	for (i=0; i < N; i++) {
		A[i] = i;
		B[i] = &A[i];
	}

	manup_array(B, N);
	printf("Array A: \n");

	for (i=0; i < N; i++) {
		printf("%d", A[i]);
		printf("\t");
	}
	printf("\n");


	printf("Array B: \n");

	for (i=0; i < N; i++) {
		printf("%d", *B[i]);
		printf("\t");
	}

	printf("\n");
	return 0;
	
}

