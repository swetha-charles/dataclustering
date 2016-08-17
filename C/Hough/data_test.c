#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"



void print_specfic_x(int row, int column){
    struct data* data = retrieve_data(55681, 3,"DATA/x.dat", "DATA/y.dat");
    int no_of_columns = data->no_of_columns;
    printf("row: %i, column: %i, %e\n", row, column, data->data_x[(row * no_of_columns) + column]);

    destroy_data_array(data);
}

void print_specfic_y(int row, int column){
    struct data* data = retrieve_data(55681, 3,"DATA/x.dat", "DATA/y.dat");
    int no_of_columns = data->no_of_columns;
    printf("row: %i, column: %i, %e\n", row, column, data->data_y[(row * no_of_columns) + column]);

    destroy_data_array(data);
}

int print_specfic_y_average_1(){
    struct data* data = retrieve_data(55681, 3,"DATA/x.dat", "DATA/y.dat");
    int no_of_columns = data->no_of_columns;
    average_data(data);
    double actual = data->data_y_mean[(0 * no_of_columns) + 0];
    double expected= (-0.040494 +-0.90849 +-0.11548)/3;

    if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
        printf("Passed test 1\n");
        printf("Expected: %e\n", expected);
        printf("Actual: %e\n", actual);
        return 1;
    } else {
        printf("Failed test 1\n");

        printf("Expected: %e\n", expected);
        printf("Actual: %e\n", actual);

        return 0;
    }
}


int main(){
    int total_test = 0;
    int passed_tests = 0;
    

    passed_tests += print_specfic_y_average_1();
    printf("\n");
    total_test++;   

    printf("\nTotal tests run: %i, passed: %i\n", total_test, passed_tests );
    return 0;
}