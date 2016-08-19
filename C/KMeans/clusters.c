#include "kmeans_header.h"

/*
	This method takes in the number of data points and the number of clusters and creates
	a clusters struct to store these values.
	@param:int no_data_points
	@param: int num_clusters

	@return: struct clusters*
		The each cluster within the struct has space for 2 * (no_data_points/num_clusters) 
*/

struct clusters *initialize_clusters(int no_data_points, int num_clusters){
	
	struct clusters* clusters = malloc(sizeof(struct clusters));

	int **cluster_array = malloc(sizeof(int*) * num_clusters);
	int *current_size = malloc(sizeof(int) * num_clusters);
	int *max_size = malloc(sizeof(int) * num_clusters);

	int average_points_per_cluster = (no_data_points/num_clusters) + 1;

	int i = 0;

	for(i = 0; i < num_clusters; i++){ 
		cluster_array[i] = malloc(sizeof(int) * 2 * average_points_per_cluster);
		max_size[i] = 2 * average_points_per_cluster;
		current_size[i] = 0;
	}


	clusters->cluster_array = cluster_array;


	clusters->current_size = current_size;
	clusters->num_clusters = num_clusters;
	clusters->max_size = max_size;
	return clusters;
}

/*
	This method frees memory allocated to a cluster struct 
	@param: struct clusters* clusters
*/

void destroy_clusters(struct clusters* clusters){
	int num_clusters = clusters->num_clusters;
	int i = 0;

	

	for(i = 0; i < num_clusters;i++){
		free(clusters->cluster_array[i]);
	}
	free(clusters->cluster_array);
	free(clusters->current_size);
	free(clusters->max_size);
	free(clusters);

}


/*
Takes in two clusters. Copies all the values from original to the copy. 
@param: struct clusters original, struct clusters copy 
*/

void deep_copy(struct clusters* original, struct clusters* copy){
	int i = 0;
	int j = 0 ;


	int orig_num_clusters = original->num_clusters;
	int copy_num_clusters = copy->num_clusters;
	
	//test that the two structs are set up to hold the same number of clusters
	if(orig_num_clusters != copy_num_clusters){
		fprintf(stdout, "ERROR: attempting to copy two dissimlar structs\n");
		exit(-1);
	}

	//free the copy's cluster array
	for(i = 0; i < copy_num_clusters; i++){
		free(copy->cluster_array[i]);
	}
	free(copy->cluster_array);
	free(copy->current_size);
	free(copy->max_size);

	
	//allocate new memory for the copy
	int** copy_cluster_array = malloc(sizeof(int*) * orig_num_clusters);
	int* copy_cluster_max_size = malloc(sizeof(int) * orig_num_clusters);
	int* copy_cluster_current_size = malloc(sizeof(int) * orig_num_clusters);

	for( i = 0; i < orig_num_clusters; i++){
		int orig_max_size = original->max_size[i];

		copy_cluster_array[i] = malloc(sizeof(int) * orig_max_size);
		copy_cluster_max_size[i] = orig_max_size;
		copy_cluster_current_size[i] = 0;
	}

	//set the struct to the new values 
	copy->cluster_array = copy_cluster_array;
	copy->current_size = copy_cluster_current_size;
	copy->max_size = copy_cluster_max_size;


	//copy original cluster array
	for (i = 0; i < orig_num_clusters; i++){
		int orig_size = original->current_size[i];
		int copy_max_size = copy->max_size[i];

		for(j = 0; j < orig_size; j++){
			int val = ((original->cluster_array)[i])[j];

			if(j < copy_max_size){
				((copy->cluster_array)[i])[j] = val;
				(copy->current_size[i])++;

			} else {
				//reallocate memory
				int success = reallocate_memory(original, i);
				copy_max_size = copy->max_size[i];

				if((success == 0) && (j < copy_max_size)){
					((copy->cluster_array)[i])[j] = val;
					(copy->current_size[i])++;

				} else {
					fprintf(stdout, "ERROR: Reallocation failed \n");
					exit(-1);
				}
			}
		}
	}

	//current size array will have been automatically copied
	
	//num clusters should be the same anyway
}

/*
	When given a cluster, this will reset the cluster to allow it to be rewritten.
	It does this by setting current size to 0. 

	@param: struct clusters* cluster, cluster to be rewritten
*/
void reset_cluster(struct clusters* cluster){
	int num_clusters = cluster->num_clusters;

	int i = 0;

	for(i = 0; i < num_clusters; i++){
		cluster->current_size[i] = 0;
	}
}

/*
 	This method aims to reallocate memory for a given cluster. It attempts to double the cluster's max size. 
 	@param: struct clusters* clusters, the struct in which we perform reallocate
 	@param: int cluster_no, the cluster number within the struct for which we wish to increase memory
*/

int reallocate_memory(struct clusters* clusters, int cluster_no){

	int current_max = clusters->max_size[cluster_no];
	int* new_cluster_memory = realloc(clusters->cluster_array[cluster_no], current_max * 2 * sizeof(*new_cluster_memory));

	if(new_cluster_memory){
		clusters->max_size[cluster_no] = current_max*2;
		clusters->cluster_array[cluster_no] = new_cluster_memory;
		return 0;
	} else {
		fprintf(stdout, "ERROR: reallocate has failed for\n");
		return 1;
	}
	
}

/*
	This method calculates the set difference between the original cluster's clusters and the new cluster's clusters
	@param: struct clusters* original_clusters
		cluster to compare
	@param: struct clusters* new_clusters
		cluster to compare
	@return: int
		total count of set difference between original and new clusters
*/
int check_for_cluster_change(struct clusters* original_clusters, struct clusters* new_clusters){
	int num_clusters = original_clusters->num_clusters;

	int i = 0;
	int j = 0;
	int k = 0;
	int set_diff = 0;
	for (i = 0; i < num_clusters; i++){
		int orig_size = original_clusters->current_size[i];
		int new_size = new_clusters->current_size[i];
		int same = 0;
		
		for(j = 0; j < orig_size; j++){
			int orig_val = (original_clusters->cluster_array[i])[j];
			
			for(k = 0; k < new_size; k++){
				int new_val = (new_clusters->cluster_array[i])[k];
				if(orig_val == new_val){
					same++;
					break;
				}
			}
		}

		set_diff += abs(orig_size - same) + (abs(new_size - same));
		//printf("cluster %i, cumul setdiff: %i\n", i, set_diff);
	}
	return set_diff;

}

/*
	Clusters given data into given clusters
	
	

*/
void initial_clustering(int num_clusters, struct clusters* clusters, struct data* data){

	int num_data_points = data->no_of_rows;
	int avg_points_per_cluster = (num_data_points/num_clusters) + 1;

	int** cluster_array = clusters->cluster_array;
	int* cluster_max_size = clusters->max_size;

	int* cluster_current_size = clusters->current_size;
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

	}

		
}


void display_cluster(struct clusters* cluster, int cluster_no){
	int size = cluster->current_size[cluster_no];

	int i = 0;
	for(i = 0 ; i < size; i++){
		printf("%i\n", ((cluster->cluster_array)[cluster_no])[i]);
	}
}


void display_cluster_sizes(struct clusters* cluster){
	int num_clusters = cluster->num_clusters;

	int i = 0;

	for(i = 0 ; i < num_clusters; i ++){
		printf("Cluster %i, size: %i\n", i,(cluster->current_size)[i]);
	}
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