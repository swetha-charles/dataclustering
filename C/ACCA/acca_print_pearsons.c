#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

void print_av_sim(){
	struct data* data = retrieve_data(100, 3,"DATA/data.txt");
    int no_of_columns = data->no_of_columns;
   

    int no_clusters = 7;
    struct clusters *original_clusters = initialize_clusters(100, no_clusters);
  
	random_sort_data(data);

   FILE* cluster_file = fopen("cluster_0_data.txt", "w");
   initial_random_clustering(no_clusters, original_clusters, data);

   	int c = 0;

   		int** cluster_array = original_clusters->cluster_array;
		int* cluster = cluster_array[c];

		int* size_clusters = original_clusters->current_size;
		int size_cluster = size_clusters[c];

		int j, k;

		for(k = 0 ; k < size_cluster; k++){
			int index  = cluster[k];
			for(j = 0; j  < no_of_columns; j++){
        		fprintf(cluster_file, "%e, ",  data->data_array[(index * no_of_columns) + j]);
       
        }

        fprintf(cluster_file, "\n");
    
		}

   	
   	FILE* av_sim = fopen("av_sim_cluster_0.txt", "w");

	calculate_average_correlation_for_cluster(original_clusters, data, 0);

	float **av_similarity_array = original_clusters->av_similarity_array;
	int current_cluster_size = (original_clusters->current_size)[0];
	float* current_av_cluster = av_similarity_array[0];
	
	int current_point = 0;


	for(current_point = 0; current_point < current_cluster_size; current_point++){

		fprintf(av_sim, "%e\n", current_av_cluster[current_point]);
	}


	FILE* pearsons = fopen("cluster_0_pc_1.txt", "w");


	for(c = 0; c < 1; c++){
		int** cluster_array = original_clusters->cluster_array;

		int* cluster = cluster_array[c];

		int* size_clusters = original_clusters->current_size;
	
		int size_cluster = size_clusters[c];

		int i = 0;
		j = 0;

		for(i = 0 ; i < size_cluster; i++){
			int x1 = cluster[i];
			for(j = 0 ; j < size_cluster; j++){
			 	int x2 = cluster[j];
			 	fprintf(pearsons, "%e, ", calculate_pearsons_similarity(x1, x2, data));
			}
			fprintf(pearsons, "\n");
		}

	}

   	fclose(pearsons);
   	fclose(av_sim);
   	fclose(cluster_file);

	destroy_clusters(original_clusters);
    destroy_data_array(data);
}


void test_pearsons(){
	struct data* data = retrieve_data(100, 3,"DATA/data.txt");
    int no_of_columns = data->no_of_columns;
   

    int no_clusters = 7;
    struct clusters *original_clusters = initialize_clusters(100, no_clusters);
  
	random_sort_data(data);

   	FILE* cluster_file = fopen("cluster_0_data.txt", "w");
   	initial_random_clustering(no_clusters, original_clusters, data);

   	int c = 0;

   	int** cluster_array = original_clusters->cluster_array;
	int* cluster = cluster_array[c];

	int* size_clusters = original_clusters->current_size;
	int size_cluster = size_clusters[c];

		int j, k;

		for(k = 0 ; k < size_cluster; k++){
			int index  = cluster[k];
			for(j = 0; j  < no_of_columns; j++){
        		fprintf(cluster_file, "%e, ",  data->data_array[(index * no_of_columns) + j]);
       
        }

        fprintf(cluster_file, "\n");
    
		}

   	
   FILE* pearsons = fopen("cluster_0_pc_1.txt", "w");


	for(c = 0; c < 1; c++){
		int** cluster_array = original_clusters->cluster_array;

		int* cluster = cluster_array[c];

		int* size_clusters = original_clusters->current_size;
	
		int size_cluster = size_clusters[c];

		int i = 0;
		j = 0;

		for(i = 0 ; i < size_cluster; i++){
			int x1 = cluster[i];
			for(j = 0 ; j < size_cluster; j++){
			 	int x2 = cluster[j];
			 	fprintf(pearsons, "%e, ", calculate_pearsons_similarity(x1, x2, data));
			}
			fprintf(pearsons, "\n");
		}

	}

   	fclose(pearsons);
   	fclose(cluster_file);
	destroy_clusters(original_clusters);
    destroy_data_array(data);
}
int main(int argc, char const *argv[])
{
	print_av_sim();
	return 0;
}