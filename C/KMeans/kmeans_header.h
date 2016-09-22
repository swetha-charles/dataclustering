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
void initial_clustering(int num_clusters, struct clusters* clusters, struct data* data);
void deep_copy(struct clusters* original, struct clusters* copy);
int reallocate_memory(struct clusters* clusters, int cluster_no);
int check_for_cluster_change(struct clusters* original_clusters, struct clusters* new_clusters);
void display_cluster(struct clusters* cluster, int cluster_no);
void display_cluster_sizes(struct clusters* cluster);
void print_cluster_file(int cluster_no, struct clusters* cluster, FILE* file);


//Data
struct data* retrieve_data(int no_of_data_points, int columns,  char* filename);
void random_sort_data(struct data* data);
void destroy_data_array(struct data* data);
void reset_cluster(struct clusters* cluster);

//Kmeans
float calculate_euclidean_distance(float x1, float y1, float z1, float x2, float y2, float z2);
int calculate_best_cluster(int data_index, struct data* data, float* centroids, int num_clusters, int num_columns);
float* initial_random_set_centroids(int num_clusters, int num_columns, struct data* data);
void move_index_to_new_cluster(struct clusters* clusters, int cluster_no, int data_index);
float* calculate_means_of_cluster(struct clusters* cluster, int cluster_no, struct data *data, float* mean);
void do_kmeans(int num_clusters, struct data* data);
float calculate_average_error(struct clusters* cluster, struct data* data , int cluster_no, float* centroids);

//Testing suites
int update_result(int result, int update_val);
void suite_tests_cluster();
void suite_tests_kmeans();

