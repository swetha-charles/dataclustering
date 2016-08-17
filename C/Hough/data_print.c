#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"

void print_x(){
	struct data* data = retrieve_data(55700, 3,"DATA/x.dat", "DATA/y.dat");
    int i, j;
    int no_of_columns = data->no_of_columns;
    int no_of_rows = data->no_of_rows;
    printf("X data points\n");
    for(i = 0; i < no_of_rows; i++){
        for(j = 0; j  < no_of_columns; j++){
        printf("%e ",  data->data_y[(i * no_of_columns) + j]);
       
        }
        printf("\n");
    }

    destroy_data_array(data);
}

void print_ys(){
	struct data* data = retrieve_data(55700, 3,"DATA/x.dat", "DATA/y.dat");
    int i, j;
    int no_of_columns = data->no_of_columns;
    int no_of_rows = data->no_of_rows;
    printf("X data points\n");
    for(i = 0; i < no_of_rows; i++){
        for(j = 0; j  < no_of_columns; j++){
        printf("%e ",  data->data_y[(i * no_of_columns) + j]);
       
        }
        printf("\n");
    }

    destroy_data_array(data);
}
