#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>

//Date
struct data{
	int no_of_rows;
	int no_of_columns;
	float* data_array;
	int* data_index;


	
};

struct clusters{
	int **cluster_array;
	int *current_size;
	int *max_size;
	int num_clusters;
};

//Clusters
struct clusters *initialize_clusters(int no_data_points, int num_clusters);
void destroy_clusters(struct clusters* clusters);
void deep_copy(struct clusters* original, struct clusters* copy);
int reallocate_memory(struct clusters* clusters, int cluster_no);
int check_for_cluster_change(struct clusters* original_clusters, struct clusters* new_clusters);

//Data
struct data* retrieve_data(int no_of_data_points, int columns,  char* filename);
void random_sort_data(struct data* data);
void destroy_data_array(struct data* data);
void reset_cluster(struct clusters* cluster);