#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

void print_data(struct data* data){
    // struct data* data = retrieve_data(55681, 3,"DATA/data.txt");
    int i, j;
    int no_of_columns = data->no_of_columns;
    int no_of_rows = data->no_of_rows;

    FILE* data_file = fopen("data.txt", "w");

    for(i = 0; i < no_of_rows; i++){
        for(j = 0; j  < no_of_columns; j++){
        fprintf(data_file, "%e, ",  data->data_array[(i * no_of_columns) + j]);
       
        }
        fprintf(data_file, "\n");
    }

    fclose(data_file);
 }


void print_random_data(){
	struct data* data = retrieve_data(55681, 3,"DATA/data.txt");
       int no_of_columns = data->no_of_columns;
    int no_of_rows = data->no_of_rows;
       int i, j;
  

 	random_sort_data(data);

    FILE* random_file = fopen("rand_data.txt", "w");
       for(i = 0; i < no_of_rows; i++){
            for(j = 0; j  < no_of_columns; j++){
                int index = (data->data_index)[i];
                fprintf(random_file, "%e, ",  data->data_array[(index * no_of_columns) + j]);
       
        }
                fprintf(random_file, "\n");
    }



    fclose(random_file);

    destroy_data_array(data);
}

void print_random_indexes(){
    struct data* data = retrieve_data(55681, 3,"DATA/data.txt");
    
    int no_of_rows = data->no_of_rows;
    int i;
    int* data_index = data->data_index;
  
  

    random_sort_data(data);

    FILE* random_file = fopen("random_indexes.txt", "w");
       for(i = 0; i < no_of_rows; i++){

        fprintf(random_file, "%i, ",  data_index[i]);  
        fprintf(random_file, "\n");
    }



    fclose(random_file);

    destroy_data_array(data);
    }


/*int main(int argc, char const *argv[])
{
    print_random_indexes();
	return 0;
}


*/