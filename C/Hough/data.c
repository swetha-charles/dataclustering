#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hough_header.h"

int no_of_columns;
int no_of_rows;


struct data *create_data_array(int size, int columns){
    double *data_x = malloc(sizeof(double) * size * columns);
    double *data_y = malloc(sizeof(double) * size * columns);
    double *data_x_mean =  malloc(sizeof(double) * size);
    double *data_y_mean = malloc(sizeof(double) * size);

    struct data *data = malloc(sizeof(struct data));
    data->data_x = data_x;
    data->data_y = data_y;
    data->data_x_mean = data_x_mean;
    data->data_y_mean = data_y_mean;

    data->no_of_rows = size;
    data->no_of_columns = columns;
    return data;
};

void destroy_data_array(struct data* data){
    free(data->data_x);
    free(data->data_y);

    free(data->data_x_mean);
    free(data->data_y_mean);
    
    free(data);
}

void read_line(char line[], struct data *data, int row ,int signal)
{
    char* tok;
    int column = 0;
    //strtok breaks up the given line based on the ',' delimeter
    for (tok = strtok(line, ","); tok!=NULL; tok = strtok(NULL, ",\n")){
        double x = convert_char_to_int(tok);

        if(signal == 0){
             store_x1_data(data, x, row, column);

        } else {
            store_x2_data(data, x, row, column);
        }
        column++;
    }
}

double convert_char_to_int(char *text){
    char* ptr;
    double ret = strtod(text, &ptr);

    return ret;
}

struct data* retrieve_data(int no_of_data_points, int columns,  char* filename_x, char* filename_y){

    struct data *data = create_data_array(no_of_data_points, columns);
    no_of_columns = columns;
    no_of_rows = no_of_data_points;

   
       //opens file in read mode
    FILE* stream1 = fopen(filename_x, "r");
    char line[1024];
     //fgets keeps going till it reads 1023 characters OR EOF OR return 
    int row = 0;
    while (fgets(line, 1024, stream1)){
        char* tmp = strdup(line);
        //nb: the third variable, 0 or i, is used to indicate whether we're reading x data or y data 
        read_line(tmp, data, row,0);
        // NOTE strtok clobbers tmp
        free(tmp);
        row++;
    }

    //reset counters
    row = 0;
    fclose(stream1);

    FILE* stream2 = fopen(filename_y, "r");
    char line2[1024];
     //fgets keeps going till it reads 1023 characters OR EOF OR return 
    while (fgets(line2, 1024, stream2)){
        char* tmp = strdup(line2);
        read_line(tmp, data,row, 1);
        // NOTE strtok clobbers tmp
        free(tmp);
        row++;
    }

    fclose(stream2);
    return data; 
}

void store_x1_data(struct data *data, double x1, int row, int column){
    assert(row < no_of_rows);
    assert(column < no_of_columns);
    data->data_x[(row * (no_of_columns)) + column] = x1;
  
}

void store_x2_data(struct data *data, double x2, int row, int column){
    assert(row < no_of_rows);
    assert(column < no_of_columns);

    data->data_y[(row * (no_of_columns)) + column] = x2;
}

void average_data(struct data* data){
    int total_rows = data->no_of_rows;
    int total_columns = data->no_of_columns;
    int r = 0;
    int c = 0;
    
    double average_x = 0;
    double average_y = 0;

    for(r = 0; r < total_rows; r++){
        for(c = 0; c < total_columns; c++){

            average_x += data->data_x[( r * total_columns) + c];
            average_y += data->data_y[( r * total_columns) + c];
        }

        data->data_x_mean[r] = (average_x / total_columns);
        data->data_y_mean[r] = (average_y / total_columns);

        average_x = 0;
        average_y = 0;
    }



}

