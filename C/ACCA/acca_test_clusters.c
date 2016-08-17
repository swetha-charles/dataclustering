#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 



void print_cluster_index(){

	int no_clusters = 7;
	struct clusters *original_clusters = initialize_clusters(55681, no_clusters);

	struct data* data = retrieve_data(55681, 3,"DATA/data.txt");
	random_sort_data(data);

	initial_random_clustering( no_clusters, original_clusters, data);
	int c = 0;

    FILE* cluster_file = fopen("cluster_indexes.txt", "w");

	for(c = 0; c < no_clusters; c++){
		int** cluster_array = original_clusters->cluster_array;

		int* cluster = cluster_array[c];

		int* size_clusters = original_clusters->current_size;
	
		int size_cluster = size_clusters[c];

		int i = 0;

		for(i = 0 ; i < size_cluster; i++){
			fprintf(cluster_file, "%i,\n", cluster[i]);
		}

	}

	fclose(cluster_file);
	destroy_clusters(original_clusters);
	destroy_data_array(data);

}

void print_cluster_data(){

	int no_clusters = 7;

	struct clusters *original_clusters = initialize_clusters(55681, no_clusters);
	

	struct data* data = retrieve_data(55681, 3,"DATA/data.txt");
	random_sort_data(data);

	initial_random_clustering(no_clusters, original_clusters, data);
    
    int no_of_columns = data->no_of_columns;

    FILE* cluster_file = fopen("cluster_data.txt", "w");
   
   	int c = 0;
   	for(c =0 ; c< no_clusters; c++){
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

   	}

   	fclose(cluster_file);

	destroy_clusters(original_clusters);
	destroy_data_array(data);

}


void verify_new_cluster_av_corr(){
	int num_clusters = 7;

	struct clusters *original_cluster = initialize_clusters(100, num_clusters);
	struct clusters *new_cluster = initialize_clusters(100, num_clusters);
	int current_cluster  = 0;

	struct data* data = retrieve_data(100, 3,"DATA/data.txt");
	random_sort_data(data);

	initial_random_clustering(num_clusters, original_cluster, data);
	print_data(data);



	
	//calculate average correlation similarity
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(original_cluster, data, current_cluster);
	}


		
	//create the new clusters with a data point each
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		int max_index = find_max_av(original_cluster, current_cluster);

		if(max_index >= 0){ //using -5 as tombstones in old cluster av
			swap_max_to_new_cluster(new_cluster, original_cluster, current_cluster, max_index);
			remove_max_from_old_cluster(original_cluster, current_cluster, max_index);

		} else {
			fprintf(stderr, "Attempted to find max on empty cluster\n");
			exit(-1);
			} 

		}

	FILE* orig_c = fopen("orig_clusters.txt", "w");
	FILE* orig_s = fopen("orig_clusters_size.txt", "w");
    
  	print_all_clusters(original_cluster, orig_c, orig_s);


	FILE* new_c = fopen("new_clusters.txt", "w");
	FILE* new_s = fopen("new_clusters_size.txt", "w");
    
  	print_all_clusters(new_cluster, new_c, new_s);


    int data_index = 0;
    int new_cluster_index = 0;
    int old_cluster_index = 0;
    FILE* avc = fopen("average_correlation.txt", "w");

    for(old_cluster_index = 0; old_cluster_index < num_clusters; old_cluster_index++){
    	int orig_cluster_size = (original_cluster->max_memory_occupied)[old_cluster_index];

   		for(data_index = 0; data_index < orig_cluster_size; data_index++){
   			
   			if(	((original_cluster->cluster_array)[old_cluster_index])[data_index] != -1){

   				for(new_cluster_index = 0; new_cluster_index < num_clusters; new_cluster_index++){

   					int data_point_index = ((original_cluster->cluster_array)[old_cluster_index])[data_index];
   					int new_cluster_point_index = ((new_cluster->cluster_array)[new_cluster_index])[0];

  // 					float data_point_actual = (data->data_array)[data_point_index * 3];
//   					float cluster_point_actual = (data->data_array)[new_cluster_point_index * 3];

   					float av_sim = calculate_average_correlation_with_new_cluster(new_cluster, data, data_point_index, new_cluster_index);
   				//	float pearsons_coeff = calculate_pearsons_similarity(data_point_index, new_cluster_point_index, data);
   				//	printf("avsim: %f, pearsons_coeff: %f\n", av_sim, pearsons_coeff);
    			 	fprintf(avc, " %i, %i, %f\n",data_point_index,new_cluster_point_index,av_sim); ;
    			 	//calculate_average_correlation_with_new_cluster(new_cluster, data, data_index, new_cluster_index) 
	    		}
   			}
    	
	    }
 	   

    }

    fclose(avc);


	destroy_clusters(new_cluster);
	destroy_clusters(original_cluster);
	destroy_data_array(data);
}

void verify_best_new_cluster(){
	int num_clusters = 7;

	struct clusters *original_cluster = initialize_clusters(100, num_clusters);
	struct clusters *new_cluster = initialize_clusters(100, num_clusters);
	int current_cluster  = 0;

	struct data* data = retrieve_data(100, 3,"DATA/data.txt");
	random_sort_data(data);

	initial_random_clustering(num_clusters, original_cluster, data);
	print_data(data);



	
	//calculate average correlation similarity
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(original_cluster, data, current_cluster);
	}


		
	//create the new clusters with a data point each
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		int max_index = find_max_av(original_cluster, current_cluster);

		if(max_index >= 0){ //using -5 as tombstones in old cluster av
			swap_max_to_new_cluster(new_cluster, original_cluster, current_cluster, max_index);
			remove_max_from_old_cluster(original_cluster, current_cluster, max_index);

		} else {
			fprintf(stderr, "Attempted to find max on empty cluster\n");
			exit(-1);
			} 

		}

	FILE* orig_c = fopen("orig_clusters.txt", "w");
	FILE* orig_s = fopen("orig_clusters_size.txt", "w");
    
  	print_all_clusters(original_cluster, orig_c, orig_s);


	FILE* new_c = fopen("new_clusters.txt", "w");
	FILE* new_s = fopen("new_clusters_size.txt", "w");
    
  	print_all_clusters(new_cluster, new_c, new_s);


    int data_index = 0;
    int old_cluster_index = 0;
    FILE* best_cluster_file = fopen("best_cluster.txt", "w");

    for(old_cluster_index = 0; old_cluster_index < num_clusters; old_cluster_index++){
    	int orig_cluster_size = (original_cluster->max_memory_occupied)[old_cluster_index];

   		for(data_index = 0; data_index < orig_cluster_size; data_index++){
   			
   			if(	((original_cluster->cluster_array)[old_cluster_index])[data_index] != -1){

   					int data_point_index = ((original_cluster->cluster_array)[old_cluster_index])[data_index];
   					//int new_cluster_point_index = ((new_cluster->cluster_array)[new_cluster_index])[0];

  // 					float data_point_actual = (data->data_array)[data_point_index * 3];
//   					float cluster_point_actual = (data->data_array)[new_cluster_point_index * 3];

   					int best_cluster = calculate_best_fit_with_new_clusters(data_point_index, original_cluster, new_cluster, data);
   				//	float pearsons_coeff = calculate_pearsons_similarity(data_point_index, new_cluster_point_index, data);
   				//	printf("avsim: %f, pearsons_coeff: %f\n", av_sim, pearsons_coeff);
    			 	fprintf(best_cluster_file, "%i, %i\n",data_point_index, best_cluster); 
    			 	//calculate_average_correlation_with_new_cluster(new_cluster, data, data_index, new_cluster_index) 
	    		}
   			
    	
	    }
 	   

    }

    fclose(best_cluster_file);


	destroy_clusters(new_cluster);
	destroy_clusters(original_cluster);
	destroy_data_array(data);
}

void verify_moving_cluster(){
	int num_clusters = 7;

	struct clusters *original_cluster = initialize_clusters(100, num_clusters);
	struct clusters *new_cluster = initialize_clusters(100, num_clusters);
	int current_cluster  = 0;

	struct data* data = retrieve_data(100, 3,"DATA/data.txt");
	random_sort_data(data);

	initial_random_clustering(num_clusters, original_cluster, data);
	print_data(data);



	
	//calculate average correlation similarity
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(original_cluster, data, current_cluster);
	}


		
	//create the new clusters with a data point each
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		int max_index = find_max_av(original_cluster, current_cluster);

		if(max_index >= 0){ //using -5 as tombstones in old cluster av
			swap_max_to_new_cluster(new_cluster, original_cluster, current_cluster, max_index);
			remove_max_from_old_cluster(original_cluster, current_cluster, max_index);

		} else {
			fprintf(stderr, "Attempted to find max on empty cluster\n");
			exit(-1);
			} 

		}

	FILE* orig_c = fopen("orig_clusters.txt", "w");
	FILE* orig_s = fopen("orig_clusters_size.txt", "w");
    
  	print_all_clusters(original_cluster, orig_c, orig_s);


	FILE* new_c = fopen("new_clusters_ini.txt", "w");
	FILE* new_s = fopen("new_clusters_size_ini.txt", "w");
    
  	print_all_clusters(new_cluster, new_c, new_s);


    int data_index = 0;
    int old_cluster_index = 0;
    
    FILE* corr_file = fopen("corr.txt", "w");
    FILE* pearsons_file = fopen("pearsons.txt", "w");
    FILE* best_cluster_file = fopen("best_cluster.txt", "w");

    for(old_cluster_index = 0; old_cluster_index < num_clusters; old_cluster_index++){
    	int orig_cluster_size = (original_cluster->max_memory_occupied)[old_cluster_index];

   		for(data_index = 0; data_index < orig_cluster_size; data_index++){
   			
   			int data_point_index = ((original_cluster->cluster_array)[old_cluster_index])[data_index];
   			if(data_point_index != -1){

   					
   					
 					
 			


   					//print av_Corr
   					int i = 0;
   					int j = 0;
   					for(i = 0; i < num_clusters; i++){
						fprintf(corr_file,"%i,%i, %f\n" ,data_point_index,i,calculate_average_correlation_with_new_cluster(new_cluster, data, data_point_index, i));
						int size_n = (new_cluster->current_size)[i];
						for( j = 0; j < size_n; j++ ){
							int x_j = ((new_cluster->cluster_array)[i])[j];
							float pears = calculate_pearsons_similarity(data_point_index, x_j, data);
							fprintf(pearsons_file, "%i, %i,%i, %i, %f\n",data_point_index,x_j, i, j, pears );
						}
					}
   					
   					int best_cluster = calculate_best_fit_with_new_clusters(data_point_index, original_cluster, new_cluster, data);
   					add_val_to_new_cluster(new_cluster, best_cluster, data_point_index, 0);
    			 	
    			 	fprintf(best_cluster_file, "%i, %i\n",data_point_index, best_cluster); 
					//remove_val_from_old_cluster(original_cluster, old_cluster_index, data_point_index);
   			 	//calculate_average_correlation_with_new_cluster(new_cluster, data, data_index, new_cluster_index) 
	    		}
  	    }
 	   

    }

    fclose(pearsons_file);
    fclose(best_cluster_file);
    fclose(corr_file);

	destroy_clusters(new_cluster);
	destroy_clusters(original_cluster);
	destroy_data_array(data);
}


void verify_cumulative_average_correlation(){
	int num_clusters = 7;

	struct clusters *original_cluster = initialize_clusters(100, num_clusters);
	//struct clusters *new_cluster = initialize_clusters(100, num_clusters);
	int current_cluster  = 0;

	struct data* data = retrieve_data(100, 3,"DATA/data.txt");
	random_sort_data(data);

	initial_random_clustering(num_clusters, original_cluster, data);
	print_data(data);

	FILE* orig_c = fopen("orig_clusters.txt", "w");
	FILE* orig_s = fopen("orig_clusters_size.txt", "w");
    
  	print_all_clusters(original_cluster, orig_c, orig_s);



	
	//calculate average correlation similarity
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(original_cluster, data, current_cluster);
	}

	int i = 0;
	//go throught second cluster and match to first cluster
	FILE* av_corr_file = fopen("av_corr.txt", "w");
	int size = (original_cluster->current_size)[1];
	
	for( i = 0; i < size; i ++){
		int data_ind = ((original_cluster->cluster_array)[1])[i];
		float av_corr = calculate_average_correlation_with_new_cluster(original_cluster, data, data_ind, 0);
		fprintf(av_corr_file, "%i, %f\n", data_ind,av_corr);

	}


	

	//
	destroy_clusters(original_cluster);
	destroy_data_array(data);
	fclose(av_corr_file);

}
int main(int argc, char const *argv[])
{
	verify_moving_cluster();
	return 0;

}