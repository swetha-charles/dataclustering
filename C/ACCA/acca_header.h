#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>
//data
struct data{
	int no_of_rows;
	int no_of_columns;
	float* data_array;
	int* data_index;


	
};

struct clusters{
	int **cluster_array;
	float **av_similarity_array;

	int *current_size;
	int *max_size;
	int *max_memory_occupied;
	int num_clusters;

	
};


struct data *create_data_array(int size, int columns);
struct data *create_data_array(int size, int columns);
void destroy_data_array(struct data* data);
void print_data(struct data* data);


struct data* retrieve_data(int no_of_data_points, int columns,  char* filename);
void read_line(char line[], struct data *data, int row ,int signal);
float convert_char_to_int(char *text);

void store_data(struct data *data, float x, int row, int column);
void average_data(struct data* data);
void random_sort_data(struct data* data);

//ACCA

void initial_random_clustering(int num_clusters, struct clusters* clusters, struct data* data);
float calculate_pearsons_similarity(int x_i, int x_j, struct data* data);
float calculate_mean(int x_i, struct data* data);
void calculate_average_correlation_within_cluster(struct clusters* cluster,struct data* data, int current_cluster);
int calculate_best_fit_with_new_clusters(int data_index, struct clusters* original_cluster, struct clusters* new_cluster, struct data* data);
void add_val_to_new_cluster(struct clusters* new_cluster, int new_cluster_no, int current_data_index, int retry);
void remove_val_from_old_cluster(struct clusters* original_cluster, int cluster_no, int index);
void do_acca(struct data* data, int num_clusters);
int find_max_av(struct clusters* original_cluster, int cluster_no);
void swap_max_to_new_cluster(struct clusters* new_cluster, struct clusters* original_cluster, int cluster_no ,int max_i);

void remove_max_from_old_cluster(struct clusters* original_cluster, int cluster_no, int max_i);
void cleanup(struct clusters* before_original_cluster, struct clusters* original,struct clusters* new_cluster);

void print_all_clusters(struct clusters* cluster, FILE* data_file, FILE* size_file);
void print_cluster_file(int cluster_no, struct clusters* cluster, FILE* file);
void print_all_av(struct clusters* cluster, FILE* file_data, FILE* size);
void print_av(int cluster_no, struct clusters* cluster, FILE* file);

//TO BE TESTED:
float calculate_average_correlation_with_new_cluster(struct clusters* new_clusters, struct data* data, int data_index, int current_new_cluster_index);

//Clusters
struct clusters *initialize_clusters(int no_data_points, int num_clusters);
struct clusters *initialize_clusters_with_pointer(int no_data_points, int num_clusters, struct clusters* pointer);

void destroy_clusters(struct clusters* clusters);
void destroy_cluster_keep_pointer(struct clusters* clusters);
struct clusters* initialize_clusters_given_pointer(int no_data_points, int num_clusters, struct clusters* pointer);
void deep_copy(struct clusters* original, struct clusters* copy);
void reset_cluster(struct clusters* cluster);
int reallocate_memory(struct clusters* clusters, int cluster_no);
void randomise_cluster(struct clusters* cluster);
int check_for_cluster_change(struct clusters* original_clusters, struct clusters* new_clusters);

void display_cluster(struct clusters* cluster, int cluster_no);
void display_cluster_sizes(struct clusters* cluster);

//Tests: Only holds the suites of the unit tests
void suite_tests_cluster();