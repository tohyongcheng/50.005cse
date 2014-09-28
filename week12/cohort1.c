#include <stdio.h>
#include <time.h>

void printTime() {
	time_t rawTime;
	time(&rawTime);
	printf("Current local time and date: %ld\n", rawTime);
}

int main() {
	printTime();
}