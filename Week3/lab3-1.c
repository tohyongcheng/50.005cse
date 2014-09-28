#include <stdio.h>
int main () {

	int x;
	float y;
	printf("Please enter value for x: ");
	scanf("%d", &x);
	printf("Please enter value for y: ");
	scanf("%f", &y);
	printf("x is %d\n", x);
	printf("y is %f\n", y);
	int fac_x;
	fac_x = fac(x);
	printf("fac_x is: %d\n", fac_x);
	float result = fac_x * y;
	printf("The result is: %f\n", result);
	printf("---------------\n");



}

int fac(int x){
	if (x == 1) {
		return 1;
	} else {
		return x * fac(x - 1);
	}
}