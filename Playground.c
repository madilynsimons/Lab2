#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int range = 78;
	int max = 48;

	srand(time(NULL));
	char c = rand() % range + max;
	printf("%c", c);
	return 0;
}