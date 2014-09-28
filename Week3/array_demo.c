#include <stdio.h>

void rvrs_array(int *array, int length){ 
 int i; 
 for(i = 0; i!= length; i++){ 
 	array[i] += 1; 
 } 
} 

int main() { 
	int const length = 5; 
	int array[length] = { 1, 2, 3, 4, 5 };
	rvrs_array(array,length); 
	int i;

	for(i = 0; i<5; i++){ 
		printf("%d", array[i]); 
	} 

	printf("\n");

	return 0; 
}