#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>


int main(int argc, char const *argv[])
{
	struct data* data = retrieve_data(30918, 4, "./DATA/data_means.csv");
	
	int no_of_clusters = 165;
	do_acca(data, no_of_clusters);

	destroy_data_array(data);
 	

	return 0;
}

