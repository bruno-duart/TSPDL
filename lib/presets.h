#ifndef HEADERS_PRESET
#define HEADERS_PRESET

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

inline static int randint(int min, int max){
	return (rand() % (max-min+1)) + min;
}

inline static int randintavoid(int min, int max, int avoid){
	int num;
	do
		num = randint(min, max);
	while(num == avoid);
	return num;
}


#endif