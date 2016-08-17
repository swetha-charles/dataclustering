#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

struct clusters* new_cluster;

void print_cluster(int cluster_no, struct clusters* cluster){
	int* current_cluster = ((cluster->cluster_array)[cluster_no]);
	int current_size = ((cluster->current_size)[cluster_no]);
	int i = 0;
	printf("Cluster no: %i, current size: %i \n", cluster_no, current_size);
	
	for(i = 0; i < current_size; i++){
		printf("%i\n", current_cluster[i]);
	}

	

} 

float calculate_average_correlation_with_new_cluster(struct clusters* new_clusters, struct data* data, int data_index, int current_new_cluster_index){
	int* new_cluster = ( new_clusters->cluster_array)[current_new_cluster_index];
	int new_cluster_size = (new_clusters->current_size)[current_new_cluster_index];


	int comparison_point = 0;
	float sum = 0;

	for(comparison_point = 0; comparison_point < new_cluster_size; comparison_point++){
		int x_j = new_cluster[comparison_point];
		sum += calculate_pearsons_similarity(data_index, x_j, data);
	}

	float result = sum / (new_cluster_size);

	return result;
		
}

int calculate_max_av_new_clusters(float av_new_clusters[], int num_clusters){
	if(num_clusters <= 0){
		fprintf(stderr, "ERROR: size of av array is 0\n");
		exit(-1);
	}
	
	float max = av_new_clusters[0];
	int index = 0;
	int i = 0;
	for(i = 0; i < num_clusters; i++){
		if(av_new_clusters[i] > max){
			max = av_new_clusters[i];
			index = i;
		}
	}

	return index;
}


int calculate_best_fit_with_new_clusters(int data_index, struct clusters* original_cluster, struct clusters* new_cluster, struct data* data){
	int num_clusters = new_cluster->num_clusters;
	float av_new_clusters[num_clusters];
	
	int i = 0;

	for(i = 0; i < num_clusters; i++){
		av_new_clusters[i] = calculate_average_correlation_with_new_cluster(new_cluster, data, data_index, i);
	}
	int best_cluster = calculate_max_av_new_clusters(av_new_clusters, num_clusters);


	return best_cluster;
}



void display_cluster_sizes(struct clusters* cluster){
	int num_clusters = cluster->num_clusters;

	int i = 0;

	for(i = 0 ; i < num_clusters; i ++){
		printf("Cluster %i, size: %i\n", i,(cluster->current_size)[i]);
	}
}
void reallocate_cluster_memory(struct clusters* cluster, int cluster_no){
	int current_size = (cluster->current_size)[cluster_no];

	int* realloc_cluster = realloc(((cluster->cluster_array)[cluster_no]), sizeof(int) * current_size * 2);
	
	if(!realloc_cluster){
		fprintf(stderr, "ERROR: Reallocate failed\n");
		exit(-1);
	} else {
		fprintf(stdout, "INFO: Reallocate successful\n");
		((cluster->max_size)[cluster_no]) = current_size * 2;
		(cluster->cluster_array)[cluster_no] = realloc_cluster;
	}

}

void add_val_to_new_cluster(struct clusters* new_cluster, int new_cluster_no, int current_data_index, int retry){
	int current_size = (new_cluster->current_size)[new_cluster_no];
	int max_size = (new_cluster->max_size)[new_cluster_no];

	if(current_size < max_size){
		((new_cluster->cluster_array)[new_cluster_no])[current_size] = current_data_index;
		(new_cluster->current_size)[new_cluster_no]++;
		(new_cluster->max_memory_occupied)[new_cluster_no]++;
	
	} else if(retry > 1){
		fprintf(stderr, "ERROR: Could not add value to new cluster\n");
		exit(-1);
	}
	else {
		fprintf(stdout, "INFO: Cluster has run out of memory, will attempt reallocate\n");
		int success = reallocate_memory(new_cluster, new_cluster_no);
		if(success == 0){
			add_val_to_new_cluster(new_cluster, new_cluster_no, current_data_index, retry + 1);
		} else {
			printf("Reallocate failed! Exiting\n");
			exit(-1);
		}
		
		
	}
	
}

void remove_val_from_old_cluster(struct clusters* original_cluster, int cluster_no, int index){
	((original_cluster->cluster_array)[cluster_no])[index] = -1; //tombstone 
	((original_cluster->av_similarity_array)[cluster_no])[index] = 100; //tombstone

	((original_cluster->current_size)[cluster_no])--;
}


void do_acca(struct data* data, int num_clusters){
	random_sort_data(data);
	int num_data_points = data->no_of_rows;
	

	if(num_clusters > num_data_points){
		fprintf(stderr, "ERROR: Number of clusters exceeds number of data points. Reduce number of clusters \n" );
		exit(-1);
	}

	struct clusters *original_cluster = initialize_clusters(num_data_points, num_clusters);
	struct clusters *original_copy = initialize_clusters(num_data_points, num_clusters);
	struct clusters *new_cluster = initialize_clusters(num_data_points, num_clusters);
	struct clusters *before_original_cluster =  initialize_clusters(num_data_points, num_clusters);
	int set_diff_holder[3];


	initial_random_clustering(num_clusters, original_cluster, data);
	
	int repeat = 1;
	int iteration = 0;

	print_data(data);
	int max_iter = 150;
	int minimum_repeat = 5;
	while((repeat == 1) && (iteration < max_iter) && (minimum_repeat > 0)){


	printf("\nIteration number: %i\n", iteration);
		int current_cluster = 0;
		
		//calculate average correlation similarity
		for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
			calculate_average_correlation_within_cluster(original_cluster, data, current_cluster);
		}

		deep_copy(original_cluster, original_copy);
		//create the new clusters with a data point each
		for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
			int max_index = find_max_av(original_cluster, current_cluster);

			if(max_index >= 0){ //using -5 as tombstones in old cluster av
				//hold snapshot of where the points around which the new clusters will be built came from
   				swap_max_to_new_cluster(new_cluster, original_cluster, current_cluster, max_index);
   				remove_max_from_old_cluster(original_cluster, current_cluster, max_index);

			} else {
				fprintf(stderr, "Attempted to find max on empty cluster\n");
				exit(-1);
			} 
		}

		int* cluster;
		int max_memory_occupied;
		int original_index;
		int current_original_cluster = 0;
		//might be a good idea to randomise each cluster, how? 
		randomise_cluster(original_cluster);

		//now recalculate av for each new datapoint and move accordingly
		for(current_original_cluster = 0; current_original_cluster < num_clusters; current_original_cluster++){
			cluster = (original_cluster->cluster_array)[current_original_cluster];
			max_memory_occupied = (original_cluster->max_memory_occupied)[current_original_cluster];

			for(original_index = 0; original_index < max_memory_occupied; original_index++){

				if(cluster[original_index] != -1){
					int data_index = cluster[original_index];
					
					int best_new_cluster = calculate_best_fit_with_new_clusters(data_index, original_cluster, new_cluster, data);
					
					add_val_to_new_cluster(new_cluster, best_new_cluster, data_index, 0);
					
					//Not necessary to remove the old value! It will get rewritten. 
					//Ensure to reset current size and max mem later. This step is very more important. 
					//remove_val_from_old_cluster(original_cluster, current_original_cluster, original_index);
				}
			}
		}


		int set_diff;
			if(iteration == 0){
				set_diff  = check_for_cluster_change(original_copy, new_cluster);
				//populate set diff
				set_diff_holder[0] = set_diff;
				set_diff_holder[1] = set_diff;
				set_diff_holder[2] = set_diff;

				if(set_diff == 0){
					repeat = 0;
				}

			} else{
				//test the new cluster against two previous clusters 

				int set_diff_orig_vs_new;
				int set_diff_orig_orig_vs_new;
				set_diff_orig_vs_new  = check_for_cluster_change(original_copy, new_cluster);
				set_diff_orig_orig_vs_new = check_for_cluster_change(before_original_cluster, new_cluster);

				//repeat of cluster states
				if((set_diff_orig_vs_new == 0) ||(set_diff_orig_orig_vs_new == 0)){
					repeat = 0;
				}

				//set difference is increasing
				if((set_diff_orig_vs_new >= set_diff_holder[2]) && (set_diff_orig_vs_new >= set_diff_holder[1]) && (set_diff_orig_vs_new >= set_diff_holder[0])){
					minimum_repeat--;
					//last iteration, then copy to new cluster
					if(minimum_repeat == 0){
						deep_copy(original_copy, new_cluster);
						repeat = 0;
					}
				} 
			
				set_diff_holder[0] = set_diff_holder[1];
				set_diff_holder[1] = set_diff_holder[2];
				set_diff_holder[2] = set_diff_orig_vs_new;
			}



			iteration++;
			
			//not yet converged
			if((repeat == 1) &&(iteration < max_iter)){
				if(iteration > 90){
					printf("\nClusters have not converged!\n");
					printf("Before orig Cluster Sizes\n");
					display_cluster_sizes(before_original_cluster);

					printf("Old Cluster Sizes\n");
					display_cluster_sizes(original_copy);
					printf("\nNew Cluster Sizes\n");
					display_cluster_sizes(new_cluster);
				}
				cleanup(before_original_cluster, original_cluster, new_cluster);
				
			} else if((iteration == max_iter) || repeat == 0 || minimum_repeat == 0){
				
				if(repeat == 0){
					printf("\nClusters have <sort of converged>!\n");
					printf("Before old Cluster Sizes\n");
					display_cluster_sizes(before_original_cluster);
					printf("Old Cluster Sizes\n");
					display_cluster_sizes(original_cluster);
					printf("\nNew Cluster Sizes\n");
					display_cluster_sizes(new_cluster);
				}
				

				int i = 0;
				for(i = 0; i < num_clusters; i++){
					char filename[] = "cluster0.txt";
					//this will break when you do > 10 clusters, i.e i = 10
					filename[7] = (char) (i + '0');
					char* name = filename; 
					FILE* file = fopen(name, "w");
					print_cluster_file(i , new_cluster, file);
				}
				

				destroy_clusters(new_cluster);
				destroy_clusters(original_cluster);
				destroy_clusters(before_original_cluster);
				destroy_clusters(original_copy);
			}
	}

}
 




void initial_random_clustering(int num_clusters, struct clusters* clusters, struct data* data){

	int num_data_points = data->no_of_rows;
	int avg_points_per_cluster = (num_data_points/num_clusters) + 1;

	int** cluster_array = clusters->cluster_array;
	int* cluster_max_size = clusters->max_size;

	int* cluster_current_size = clusters->current_size;
	int* cluster_max_mem = clusters->max_memory_occupied;

	int* data_index = data->data_index;

	int max_size = 0;
	int current_data_index = 0;
	int cluster = 0;
	int row = 0;

	
	for(cluster = 0; cluster < num_clusters; cluster++){
		int* current_cluster = cluster_array[cluster];
		max_size = cluster_max_size[cluster];

		for(row = 0; (row < avg_points_per_cluster) && (current_data_index < num_data_points) && (row < max_size); row++){
			int d_index = data_index[current_data_index];
			current_cluster[row] = d_index;
			current_data_index++;
		}
		cluster_current_size[cluster] = row;
		cluster_max_mem[cluster] = row;//max mem tells you the maximum place in memory occupied by this cluster. 
									   //useful when size =/= no longer tell you the max position in memory occupied due to swapping

	}

		
}

void calculate_average_correlation_within_cluster(struct clusters* cluster, struct data* data ,int current_cluster_index){
	int **cluster_array = cluster->cluster_array;
	float **av_similarity_array = cluster->av_similarity_array;

	int* current_cluster = cluster_array[current_cluster_index];
	int current_cluster_size = (cluster->current_size)[current_cluster_index];

	float* current_av_cluster = av_similarity_array[current_cluster_index];
	

	int current_point = 0;
	int comparison_point = 0;
	float sum = 0;

	for(current_point = 0; current_point < current_cluster_size; current_point++){
		sum = 0;
		int x_i = current_cluster[current_point];

		for(comparison_point = 0; comparison_point < current_cluster_size; comparison_point++){
			if(comparison_point != current_point){
				
				int x_j = current_cluster[comparison_point];

				sum += calculate_pearsons_similarity(x_i, x_j, data);
			}
		}

		current_av_cluster[current_point] = sum / (current_cluster_size - 1);
		

	}

}

float calculate_pearsons_similarity(int x_i, int x_j, struct data* data){
	int no_of_columns = data->no_of_columns;
	float mean_xi = calculate_mean(x_i, data);
	float mean_xj = calculate_mean(x_j, data);

	int i = 0;
	float numerator1 = 0.0;
	float denominator1 = 0.0;
	float denominator2 = 0.0;

	for(i = 0; i < no_of_columns; i++){
		numerator1 += ((data->data_array)[(x_i * no_of_columns) + i] - mean_xi) * ((data->data_array)[(x_j * no_of_columns) + i] - mean_xj);
		denominator1 += ((data->data_array)[(x_i * no_of_columns) + i] - mean_xi) * ((data->data_array)[(x_i * no_of_columns) + i] - mean_xi);
		denominator2 += ((data->data_array)[(x_j * no_of_columns) + i] - mean_xj) * ((data->data_array)[(x_j * no_of_columns) + i] - mean_xj);
	}

	float corr_coeff =  (numerator1 / sqrt(denominator1 * denominator2));
	return corr_coeff;

}

float calculate_mean(int x_i, struct data* data){
	int no_of_columns = (data->no_of_columns);
	int no_of_rows = (data->no_of_rows);
	if(x_i >= no_of_rows){
		fprintf(stderr, "ERROR: exceeding data array\n");
	}
	int i = 0;
	float sum = 0.0;

	for(i = 0; i < no_of_columns; i++){
		sum += (data->data_array)[(x_i * no_of_columns) + i];
	}

	return (sum / no_of_columns);
}

/*
 * Should only be called if clusters have something 
*/

int find_max_av(struct clusters* original_cluster, int cluster_no){
 	

 	float *av_similarity = (original_cluster->av_similarity_array)[cluster_no];

 	int cluster_current_size = (original_cluster->current_size)[cluster_no];
	int cluster_max_mem = (original_cluster->max_memory_occupied)[cluster_no];

	int i = 0;
	int index = 0;
	float curr_max = -INFINITY;
	float val;

	//prevents checking empty clusters for max
	if(cluster_current_size > 0){

		//check through the entire are of memory occupied. 
		for( i = 0; (i < cluster_max_mem) ; i++){

			if((av_similarity[i] >= -1) && (av_similarity[i] <= 1)) {//Using 100 as a tombstone for av_sim matrix. Average correlations values will be between -1 and 1
				val = av_similarity[i];

				if(val > curr_max){
					
					curr_max = val;
					index = i;
					
				}
			} 
		}

		return index;

	} else {
		return -5;
	}
		
		
}

void swap_max_to_new_cluster(struct clusters* new_cluster, struct clusters* original_cluster, int cluster_no, int max_i){
	
	int max_val = ((original_cluster->cluster_array)[cluster_no])[max_i];

	int new_max_size = (new_cluster->max_size)[cluster_no];
	int new_current_size = ((new_cluster->current_size)[cluster_no]);

	if(new_current_size < new_max_size){
		
		((new_cluster->cluster_array)[cluster_no])[new_current_size] = max_val;
		
		(new_cluster->current_size)[cluster_no]++;	//increase current size
		(new_cluster->max_memory_occupied)[cluster_no]++; //increase max mem 

		

	} else {
		fprintf(stderr, "ERROR: Cluster has run out of memory!\n" );
	}
	

}

void remove_max_from_old_cluster(struct clusters* original_cluster, int cluster_no, int max_i){
	((original_cluster->cluster_array)[cluster_no])[max_i] = -1; //tombstone 
	((original_cluster->av_similarity_array)[cluster_no])[max_i] = 100; //tombstone

	((original_cluster->current_size)[cluster_no])--;
	
}
/*
	@param: struct clusters* before_original_cluster
	@param: struct clusters* original
	@param: struct clusters* new
	This method cleanup the clusters at the end of an ACCA iteration. 
	It copies original to before_original, new to original and finally resets new cluster. 


*/
void cleanup(struct clusters* before_original_cluster, struct clusters* original_cluster,struct clusters* new_cluster){
	deep_copy(original_cluster, before_original_cluster);
	deep_copy(new_cluster, original_cluster);
	reset_cluster(new_cluster);
}

/****************************************************************************************/
/*
	Printing!
*/
void print_all_clusters(struct clusters* cluster, FILE* data_file, FILE* size_file){
	int no_of_clusters = cluster->num_clusters;
	int i = 0;
	for ( i = 0; i < no_of_clusters; i ++){
		int* current_cluster = ((cluster->cluster_array)[i]);
		int max_size = ((cluster->max_memory_occupied)[i]);
		int current_size = ((cluster->current_size)[i]);

		fprintf( size_file, "%i\n", current_size);


		int j = 0;
		for(j = 0; j < max_size; j++){
			if(current_cluster[j] != -1){
				fprintf(data_file, "%i\n", current_cluster[j]);
			}
			
		}
	}
	

	fclose(size_file);
	fclose(data_file);

} 

void print_cluster_file(int cluster_no, struct clusters* cluster, FILE* file){
	int* current_cluster = ((cluster->cluster_array)[cluster_no]);
	int current_size = ((cluster->current_size)[cluster_no]);
	int i = 0;
		
	for(i = 0; i < current_size; i++){
		fprintf( file, "%i\n", current_cluster[i]);
	}

	fclose(file);

} 



void print_all_av(struct clusters* cluster, FILE* file_data, FILE* size){
	int i = 0;
	int no_of_clusters = cluster->num_clusters;

	for( i = 0; i < no_of_clusters; i++){
		float* current_cluster_av = ((cluster->av_similarity_array)[i]);
		int current_size = ((cluster->current_size)[i]);
		int j = 0;

		fprintf(size, "%i\n", current_size);

		for(j = 0; j < current_size; j++){
			fprintf( file_data, "%e\n", current_cluster_av[j]);
		}
	
	}
	fclose(file_data);
}

void print_av(int cluster_no, struct clusters* cluster, FILE* file){
	float* current_cluster_av = ((cluster->av_similarity_array)[cluster_no]);
	int current_size = ((cluster->current_size)[cluster_no]);
	int i = 0;

	fprintf(file, "Cluster no: %i, current size: %i \n", cluster_no, current_size);

	for(i = 0; i < current_size; i++){
		fprintf( file, "%e\n", current_cluster_av[i]);
	}

	fclose(file);

} 

void display_cluster(struct clusters* cluster, int cluster_no){
	int size = cluster->current_size[cluster_no];

	int i = 0;
	for(i = 0 ; i < size; i++){
		printf("%i\n", ((cluster->cluster_array)[cluster_no])[i]);
	}
}