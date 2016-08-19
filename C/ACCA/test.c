#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>



int main(int argc, char const *argv[])
{
	char filename[] = "./RESULTS/cluster0.txt";
	//this will break when you do > 10 clusters, i.e i = 10
	filename[17] = (char) (1 + '0');
	char* name = filename; 
	FILE* file = fopen(name, "ab+");
	fprintf(file, "WHATSUP\n");
	fclose(file);
	return 0;
}