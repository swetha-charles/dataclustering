//testing memset 

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //Gives C's library value of Pi
#include "hough_header.h"

struct test{
	float *easy_array;
};

int main(){
	struct test *t1 = malloc(sizeof(struct test));
	t1->easy_array = malloc(sizeof(float) * 5);

	int i =0;

	for(; i < 5; i ++){
		printf("%f" , t1->easy_array[i]);
	}

	free(t1->easy_array);
	free(t1);
}