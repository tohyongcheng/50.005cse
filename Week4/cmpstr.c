#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80

int main() {
	int length, diff;
	char inputBuffer[MAX_LINE];
	printf("Please type in a string: ");
	fflush(stdout);

	length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
	diff = strncmp(inputBuffer, "exit", 4);
	printf("\nResult of strncmp( %s, %s) is %d .\n", inputBuffer, "exit", diff);

	return 0;

}