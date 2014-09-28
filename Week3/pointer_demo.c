#include <stdio.h>
int main () {

	int *pointer;
	int x =3;
	pointer = &x;
	int y = *pointer;

	printf("x = %d \t pointer = %p, \t y = %d\n", x, pointer, y);
	*pointer += 1;
	printf("x = %d \t pointer = %p, \t y = %d\n", x, pointer, y);

	return 0;
}