#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>


int main(int argc, char const *argv[])
{
	struct data* data = retrieve_data(55681, 3, "./DATA/data.txt");
	
	int no_of_clusters = 100;
	do_acca(data, no_of_clusters);

	destroy_data_array(data);
 	
	return 0;
}
