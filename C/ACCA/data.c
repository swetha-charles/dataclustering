#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 


int no_of_columns;
int no_of_rows;

struct data *create_data_array(int size, int columns){
    float *data_array = malloc(sizeof(float) * size * columns);


    struct data *data_struct = malloc(sizeof(struct data));
    int* data_index = malloc(sizeof(int) * size);

    
    int i = 0;

    for(i = 0; i < size; i++){
      data_index[i] = i;
   }

    data_struct->data_array = data_array;
    data_struct->data_index = data_index;

    data_struct->no_of_rows = size;
    data_struct->no_of_columns = columns;
    return data_struct;
};


void destroy_data_array(struct data* data){
    free(data->data_array);
    free(data->data_index);
    free(data);
}

struct data* retrieve_data(int no_of_data_points, int columns,  char* filename){

    struct data *data = create_data_array(no_of_data_points, columns);
    no_of_columns = columns;
    no_of_rows = no_of_data_points;
       //opens file in read mode
    FILE* stream1 = fopen(filename, "r");
    char line[1024];
     //fgets keeps going till it reads 1023 characters OR EOF OR return 
    int row = 0;
    while (fgets(line, 1024, stream1) && (row < no_of_data_points)){
        char* tmp = strdup(line);
        read_line(tmp, data, row,0);
        // NOTE strtok clobbers tmp
        free(tmp);
        row++;
    }


    fclose(stream1);
    return data; 
}

void read_line(char line[], struct data *data, int row ,int signal)
{
    char* tok;
    int column = 0;
    //strtok breaks up the given line based on the ',' delimeter
    for (tok = strtok(line, ","); tok!=NULL; tok = strtok(NULL, ",\n")){
        float x = convert_char_to_int(tok);

   
        store_data(data, x, row, column);

        
        column++;
    }
    if(column == 0){
      printf("ERROR, no readable input found. Is your file csv?\n");
    }
}

float convert_char_to_int(char *text){
    char* ptr;
    float ret = strtod(text, &ptr);

    return ret;
}

void store_data(struct data *data, float x, int row, int column){
    if((row < no_of_rows) && (column < no_of_columns)){
      data->data_array[(row * (no_of_columns)) + column] = x;
    } else {
      fprintf(stdout, "STOP, you are attempting to store outside allocated memory" );
    }
    
  
}



/*From StackOverflow: Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(struct data* data , int n)
{

    int seed = time(NULL);
    srand(seed);

    int* data_index = data->data_index;
    if (n > 1) 
    {
        int i;
        for (i = 0; i < n - 1; i++) //n-1
        {
          int j = i + rand() / (RAND_MAX / (n - i) + 1);
         
          int temp = data_index[j];
          data_index[j] = data_index[i];
          data_index[i] = temp;

        }
    }
}

void random_sort_data(struct data* data){

    int no_data_points = data->no_of_rows;
    if(no_data_points > 0){
         shuffle(data, no_data_points);
     }
     else {
        fprintf(stdout, " 'ERROR: No data provided!'\n");
     }
   
}
