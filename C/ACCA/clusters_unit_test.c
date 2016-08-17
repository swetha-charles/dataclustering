#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
/******************************************************************************/
/*
	General method 
*/

int update_result(int result, int update_val){
	int updated_result;
	
	if(result == 0){
		updated_result = update_val;
	} else {
		//in cases where result is 1
		updated_result = result;
	}


	return updated_result;
}


/*******************************************************************************/
/*
	Testing deep copy 
*/

int compare_floats(float f1, float f2, float precision){
	
	if(abs(f1 - f2) > precision){
		return 1;
	} else {
		return 0;
	}
}


int test_cluster_equality(int** orig_cluster_array, int* orig_current_size, int** copy_cluster_array, int* copy_current_size, int num_clusters){
	
	int i = 0;
	int j = 0;
	for( i = 0; i < num_clusters; i++){
		int size_orig = orig_current_size[i];
		int size_copy = copy_current_size[i];
		assert(size_orig == size_copy);
		
		for( j = 0; j < size_orig; j++){
			int orig_val = (orig_cluster_array[i])[j];
			int copy_val = (copy_cluster_array[i])[j];
			
			if(orig_val != copy_val){
				return 1;
			}
		}

	}

	return 0;
}

int test_av_equality(float** orig_cluster_array, int* orig_current_size, float** copy_cluster_array, int* copy_current_size,int num_clusters){

	int i = 0;
	int j = 0;
	for( i = 0; i < num_clusters; i++){
		int size_orig = orig_current_size[i];
		int size_copy = copy_current_size[i];
		assert(size_orig == size_copy);
		
		for( j = 0; j < size_orig; j++){
			float orig_val = (orig_cluster_array[i])[j];
			float copy_val = (copy_cluster_array[i])[j];
			
			int result = compare_floats(orig_val, copy_val, 0.0001);
			if(result == 1){
				return 1;
			}
		}

	}

	return 0;
}

int test_array_equality(int* orig_array, int* copy_array,  int num_clusters){
	int i = 0;
	for(i = 0; i < num_clusters; i ++){
		int orig_val = orig_array[i];
		int copy_val = copy_array[i];

		if(orig_val != copy_val){
			return 1;
		}
	}
	return 0;
}

/*
	@param: struct cluster* original, struct cluster* copy
	Given these two clusters, this method checks for their equality
	@return: an int value 
		0: equal
		1: unequal
*/
int test_struct_cluster_equality(struct clusters* original, struct clusters* copy){
	
	int num_clusters = original->num_clusters;
	
	//test current size equality: everything else depends on this anyway!
	int* orig_current_size = original->current_size;
	int* copy_current_size = copy->current_size;

	int result_size = test_array_equality(orig_current_size, copy_current_size, num_clusters);
	if(result_size == 1){
		return 1;
	}
	//printf("Cluster sizes the same\n");

	//test cluster equality
	int** orig_cluster_array = original->cluster_array;
	int* orig_cluster_size = original->current_size;

	int** copy_cluster_array = copy->cluster_array;
	int* copy_cluster_size = copy->current_size;

	int result_cluster = test_cluster_equality(orig_cluster_array,orig_cluster_size, copy_cluster_array, copy_cluster_size, num_clusters);
	if(result_cluster == 1){
		return 1;
	}
	//printf("Cluster arrays the same\n");

	//test av similarity equality
	float** orig_av_array = original->av_similarity_array;
	int* orig_av_size = original->current_size;

	float** copy_av_array = copy->av_similarity_array;
	int* copy_av_size = copy->current_size;
	int result_av = test_av_equality(orig_av_array,orig_av_size, copy_av_array, copy_av_size, num_clusters);
	if(result_av == 1){
		return 1;
	}
	//printf("Cluster AV's the same\n");

	//test max_size 

	int* orig_max_size = original->max_size;
	int* copy_max_size = copy->max_size;
	int result_max_size = test_array_equality(orig_max_size, copy_max_size, num_clusters);
	if(result_max_size == 1){
		return 1;
	}

	//test max_mem 
	int* orig_max_mem = original->max_memory_occupied;
	int* copy_max_mem = copy->max_memory_occupied;
	int result_max_mem = test_array_equality(orig_max_mem, copy_max_mem, num_clusters);
	if(result_max_mem == 1){
		return 1;
	}
	//printf("Max Mems the same\n");


	//test num_clusters, final test
	int orig_num_clusters = original->num_clusters;
	int copy_num_clusters  = copy->num_clusters ;

	if(orig_num_clusters != copy_num_clusters){
 		return 1;
	} 
	//printf("Num clusters the same\n");
	//if all tests have passed, return 0
	return 0;
}

/*
 Tests whether the deep copy method functions correctly
 @return: int 
	0: deep copy method passed
	1: deep copy method failed
*/
int test_deep_copy(){
	printf("\nTesting deep copy\n");
	int num_clusters = 7;
	struct data* data = retrieve_data(100, 3, "DATA/data.txt");

	struct clusters* original = initialize_clusters(100, num_clusters);
	struct clusters *copy = initialize_clusters(100, num_clusters);

	//randomly clusters data into original
	initial_random_clustering(num_clusters, original, data);
	int current_cluster = 0;

	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(original, data, current_cluster);
	}

	//deep copy
	deep_copy(original, copy);

	int equal = test_struct_cluster_equality(original, copy);

	destroy_clusters(original);
	destroy_clusters(copy);
	destroy_data_array(data);
	if(equal == 0){
		printf("Passed deep copy\n");
	} else {
		printf("Failed deep copy\n");

	}
	return equal;
}
/* 
	End testing deep copy
*/
/**********************************************************************************************/


/**********************************************************************************************/
/*
	Testing for reset cluster
*/


 int test_cluster_empty(struct clusters *cluster){
 	int i = 0;
 	int num_clusters = cluster->num_clusters;
 	for(i = 0; i < num_clusters; i++){
 		if(cluster->current_size[i] != 0){
 		printf("method test_cluster_empty: FAILURE, cluster sizes not 0\n");
	 	return 1;
 		}
 	}

 	for(i = 0; i < num_clusters; i++){
 		if(cluster->max_memory_occupied[i] != 0){
 		printf("method test_cluster_empty: FAILURE, cluster's max sizes not 0\n");
	 	return 1;
 		}
 	}

 	return 0;
 	
 }

/*
  Rewrites a given cluster using given dummy data
  @param: cluster - cluster to rewrite
  @param: dummy_index - what to populate the cluster_array with
  @param: dummy_av - what to populate the av_similarity_array with
*/
void rewrite_dummy_data(struct clusters* cluster, int dummy_index, float dummy_av){
	int num_clusters = cluster->num_clusters;
	
	int i = 0;
	int j = 0;
	
	for(i = 0; i < num_clusters; i++){
		int max_size = cluster->max_size[i];

		for(j = 0; j < max_size; j++){
			(cluster->cluster_array[i])[j] = dummy_index;
			(cluster->av_similarity_array[i])[j] = dummy_av;

			(cluster->current_size[i])++;
			(cluster->max_memory_occupied[i])++;
		}
	}
}
/*
 @param: dummy_index - what should be found in the cluster array
 @param: dumm_av - what should be found in the av array

 Method checks whether dummy_index value fully populates cluster array and whether dummy_av value fully populates av_array


*/
int check_dummy_data(struct clusters* cluster, int dummy_index, float dummy_av){
	
	//verify that current size == max size
	int i = 0;
	int j = 0;
	int num_clusters = cluster->num_clusters;

	for(i = 0; i < num_clusters; i++){
		if((cluster->current_size)[i] != cluster->max_size[i]){
			printf("check_dummy_data: FAILURE, Cluster was not completely filled\n");
			return 1;
		}
	}
	
	//verify that current size == max mem occupied
	for(i = 0; i < num_clusters; i++){
		if((cluster->current_size)[i] != cluster->max_memory_occupied[i]){
			printf("check_dummy_data: FAILURE, max memory and current size do not match up\n");
			return 1;
		}
	}

	//verify that cluster array is made up of dummy cluster data
	for(i = 0; i < num_clusters; i++){
		int cluster_size  = (cluster->current_size)[i];
		for(j = 0; j < cluster_size; j++){
			int current_val = ((cluster->cluster_array)[i])[j];
			if(current_val != dummy_index){
				printf("check_dummy_data: FAILURE, cluster val does not match dummy index data\n");
				return 1;
			}
		}
	}



	//verify that av array is made up of dummy av data
	for(i = 0; i < num_clusters; i++){
		int cluster_size  = (cluster->current_size)[i];
		for(j = 0; j < cluster_size; j++){
			float current_val = ((cluster->av_similarity_array)[i])[j];
			if(current_val != dummy_av){
				printf("check_dummy_data: FAILURE, av val does not match dummy av data\n");
				return 1;
			}
		}
	}

	return 0;
}

/*
This method checks whether the reset method is successful. The point of the reset method is that it allows the cluster 
to be rewritten with fresh values. Using this as a template, the reset cluster method rewrites the given cluster using 
dummy values (rewrite_dummy_data). It then checks whether this rewrite was successful (check_dummy_data). Depending on
whether the rewrite was successful, the method returns an int. 

 @return: int 
 	0: reset cluster was successful
 	1: reset cluster was not successful
*/
int test_reset_cluster(){
	printf("\nTesting reset cluster\n");
	int num_clusters = 7;
	struct data* data = retrieve_data(100, 3, "DATA/data.txt");

	struct clusters* original = initialize_clusters(100, num_clusters);
	
	//randomly clusters data into original
	initial_random_clustering(num_clusters, original, data);
	int current_cluster = 0;

	//calculate AV
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(original, data, current_cluster);
	}

	reset_cluster(original);
	int result;
	result = test_cluster_empty(original);
	rewrite_dummy_data(original, 1, 0.5);
	result += check_dummy_data(original, 1, 0.5);

	destroy_data_array(data);
	destroy_clusters(original);

	if(result == 0){
		printf("Passed reset cluster\n");
	} else{
		printf("Failed reset cluster\n");
	}
	
	return result;
}

/*
 End testing reset cluster 
*/
 /****************************************************************************************/
 
 /*
 Begin testing for reallocate
 */



 /*
 This method tests whether the reallocate method correctly doubles the size of the given cluster.
 @return: int 
 	0: successful reallocate
 	1: unsuccesful reallocate

 */

 int test_reallocate_memory(){
 	printf("\nTesting reallocate memory\n");
 	int num_clusters = 7;
 	int num_data_points = 100;
 	int current_max_size[num_clusters];

 	struct clusters* original = initialize_clusters(num_data_points, num_clusters);

 	int i = 0;
 	
 	for(i = 0; i < num_clusters; i++){
		current_max_size[i] = (original->max_size)[i];
 	}
 	
 	//reallocate memory for all 
 	for(i = 0; i < num_clusters; i++){
 		int success = reallocate_memory(original, i);
 		if(success == 1){
 			printf("method test_reallocate_memory: ERROR, reallocate could not complete! \n Stopping test \n");
 			return 1;
 		}
 	}

 	//test that max size has increased 
	for(i = 0; i < num_clusters; i++){
		if((original->max_size)[i] != (2 * current_max_size[i])){
			printf("method test_reallocate_memory: ERROR, size of cluster after reallocation is not twice the original size \n");
			return 1;
		}
		
	}

	//check that you can write till the new max size
	rewrite_dummy_data(original, 1, 0.5);

	//check that that rewrite went as planned
	int result = check_dummy_data(original, 1, 0.5);

	destroy_clusters(original);
	if(result == 0){
		printf("Passed reallocate memory\n");
	} else {
		printf("Failed reallocate memory\n");

	}
 	return result;
 }

 /*
	End testing for reallocate 
*/
 /****************************************************************************************/

 /*
 	Begin testing for cleanup
 */


 /*
	This method tests that the cleanup method has correctly copied original cluster -> before_original cluster , 
	new cluster -> original cluster and the reset new cluster
	 @return: int 
	 	0: successful cleanup
	 	1: unsuccessful cleanup
 */
int test_cleanup(){
 	printf("\nTesting cleanup\n");

	int num_data_points = 100;
	int num_clusters = 7;

	struct data* data = retrieve_data(num_data_points, 3, "DATA/data.txt");
	
	//populate original cluster
	random_sort_data(data);
	struct clusters *original_cluster = initialize_clusters(num_data_points, num_clusters);
	struct clusters *original_cluster_copy = initialize_clusters(num_data_points, num_clusters);
	initial_random_clustering(num_clusters, original_cluster, data);
	int current_cluster = 0;
	//populate av array
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(original_cluster, data, current_cluster);
	}
	deep_copy(original_cluster, original_cluster_copy);

	//populate new cluster
	random_sort_data(data);
	struct clusters *new_cluster = initialize_clusters(num_data_points, num_clusters);
	struct clusters *new_cluster_copy = initialize_clusters(num_data_points, num_clusters);
	initial_random_clustering(num_clusters, new_cluster, data);
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(new_cluster, data, current_cluster);
	}
	deep_copy(new_cluster, new_cluster_copy);

	//populate before original cluster
	random_sort_data(data);
	struct clusters *before_original_cluster =  initialize_clusters(num_data_points, num_clusters);
	struct clusters *before_original_cluster_copy =  initialize_clusters(num_data_points, num_clusters);
	initial_random_clustering(num_clusters, before_original_cluster, data);
	for(current_cluster = 0; current_cluster < num_clusters; current_cluster++){
		calculate_average_correlation_within_cluster(before_original_cluster, data, current_cluster);
	}
	deep_copy(before_original_cluster, before_original_cluster_copy);

	//run cleanup
	cleanup(before_original_cluster, original_cluster, new_cluster);

	//test cluster equality
	int equal;
	int result;
	equal = test_struct_cluster_equality(before_original_cluster, original_cluster_copy);
	if(equal == 1){
		printf("method test_cleanup: FAILURE, before_original cluster not copied properly from original cluster\n");
		result = 1;
	}

	equal = test_struct_cluster_equality(original_cluster, new_cluster_copy);
	if(equal == 1){
		printf("method test_cleanup: FAILURE, original cluster not copied properly from new cluster\n");
		result = 1;
	}

	int empty = test_cluster_empty(new_cluster);
	if(empty == 1){
		printf("method test_cleanup: FAILURE, new cluster not reset properly\n");
		printf("Failed cleanup\n");
		result = 1;
	} else {
		printf("Passed cleanup\n");
		result = 0;
	}

	destroy_data_array(data);
	destroy_clusters(original_cluster);
	destroy_clusters(original_cluster_copy);
	destroy_clusters(before_original_cluster);
	destroy_clusters(before_original_cluster_copy);
	destroy_clusters(new_cluster);
	destroy_clusters(new_cluster_copy);

	return result;
} 	


 /*
 End testing for cleanup
*/
 /****************************************************************************************/
 

 /*
 	Begin testing for randomise cluster
 */
 	int test_unequal(struct clusters* randomised, struct clusters* original, double percentage_leeway){
 		int num_clusters = randomised->num_clusters;
 		int i = 0;
 		int j = 0;
 		int total_size = 0;
 		//calculate leeway
 		for(i = 0; i < num_clusters; i++){
 			int current_size = randomised->current_size[i];
 			total_size +=  current_size; 			
 		}

 		//Percentage of the data points can stay in the same place
	 	int leeway = (percentage_leeway) * total_size;
	 	int stationary_points = 0;

 		for(i = 0; i < num_clusters; i++){
 			int max_memory_occupied = randomised->max_memory_occupied[i];
 			
 			for(j = 0; j< max_memory_occupied; j++){
 				int randomised_val = (randomised->cluster_array[i])[j];
 				int original_val = (original->cluster_array[i])[j];
 				if(randomised_val == original_val){
 					stationary_points++;
 				}

 				if(stationary_points > leeway){
 					printf("method test_unequal: FAILURE, more than %i percent of points stationary\n", (int)(percentage_leeway * 100));
 					return 1;
 				}
 			}
 		}

 		return 0;
 	}

 	int test_randomise_cluster(){
 		printf("\nTesting randomise cluster\n");
 		int num_clusters = 7;
 		int num_data_points = 100;
 		struct data* data = retrieve_data(num_data_points, 3, "DATA/data.txt");


 		struct clusters *original_cluster = initialize_clusters(num_data_points, num_clusters);
		struct clusters *original_cluster_copy = initialize_clusters(num_data_points, num_clusters);
		random_sort_data(data);
		initial_random_clustering(num_clusters, original_cluster, data);
		deep_copy(original_cluster, original_cluster_copy);
 		
 		randomise_cluster(original_cluster);
 		// display_cluster(original_cluster, 0);
 		// printf("\n");
 		// display_cluster(original_cluster_copy, 0);


 		int unequal = test_unequal(original_cluster, original_cluster_copy, 0.15);
 		
 		if(unequal == 0){
 			printf("Passed randomise cluster\n");
 		} else {
 			printf("Failed randomise cluster\n");
 		}

 		destroy_data_array(data);
		destroy_clusters(original_cluster);
		destroy_clusters(original_cluster_copy);
 		return unequal;
 	}

 /*
 End testing for randomise cluster
*/
 /****************************************************************************************/

void delete_one_val(struct clusters *cluster, int cluster_no, int val_delete){
	int curr_size = cluster->current_size[cluster_no];

	int i = 0;
	//how to move shit? 
	for(i = val_delete; i < curr_size; i++){
		(cluster->cluster_array[cluster_no])[i - 1] = (cluster->cluster_array[cluster_no])[i];
	}
	curr_size = cluster->current_size[cluster_no]--;
}
 /*
 	Begin testing for cluster change
 */
 	int test_cluster_change(){
 		printf("\nTesting cluster change\n");

 		int num_data_points = 100;
 		int num_clusters = 7;

 		struct data* data = retrieve_data(num_data_points, 3, "DATA/data.txt");
		random_sort_data(data);
 		struct clusters *original_cluster = initialize_clusters(num_data_points, num_clusters);
 		struct clusters *original_cluster_copy = initialize_clusters(num_data_points, num_clusters);

		initial_random_clustering(num_clusters, original_cluster, data);
		deep_copy(original_cluster, original_cluster_copy);

		int result = 0;
 		int result_no_change = check_for_cluster_change(original_cluster, original_cluster);
 		
 		//test equivalent clusters
 		if(result_no_change != 0){
 			result = 1;
 			printf("method test_cluster_change: FAILURE, could not correctly identify 2 similar clusters\n");
 		} 

 		//make one change and see if this set diff is picked up
 		delete_one_val(original_cluster, 0, 5);
 		int result_one_change = check_for_cluster_change(original_cluster, original_cluster_copy);
 		if(result_one_change != 1){
 			printf("method test_cluster_change: FAILURE, could not correctly identify there was one change between clusters\n");
 			result = update_result(result, 1);
 		}
 		
 		//use a completely different cluster and check that the value is greater than 1! 
 		random_sort_data(data);
 		struct clusters *diff_cluster = initialize_clusters(num_data_points, num_clusters);
		initial_random_clustering(num_clusters, diff_cluster, data);

		int result_diff_cluster = check_for_cluster_change(diff_cluster, original_cluster_copy);
		
		if(result_diff_cluster <= 1){
 			printf("method test_cluster_change: FAILURE, could not correctly count differences with a very different cluster\n");
 			result = update_result(result, 1);
 		}


 		destroy_clusters(original_cluster);
 		destroy_clusters(original_cluster_copy);
 		destroy_clusters(diff_cluster);
 		destroy_data_array(data);

 		if(result == 0){
 			printf("Passed cluster change\n");
 		}
 		return result;
 	}

 /*
 	End testing for cluster change
*/
 /****************************************************************************************/

void suite_tests_cluster(){
	printf("\nClusters: Unit Tests\n");
	int tests_passed = 0;
	int tests_run = 0;
	int result;

	//test deep copy
	result = test_deep_copy();
	tests_run++;
	if(result == 0){
		tests_passed++;
	}


	//test reset cluster
	result = test_reset_cluster();
	tests_run++;
	if(result == 0){
		tests_passed++;
	}

	//test reallocate memory
	result = test_reallocate_memory();
	tests_run++;
	if(result == 0){
		tests_passed++;
	}

	//test cleanup
	result = test_cleanup();
	tests_run++;
	if(result == 0){
		tests_passed++;
	}

	//test randomise cluster
	result = test_randomise_cluster();
	tests_run++;
	if(result == 0){
		tests_passed++;
	}


	//test cluster change
	result = test_cluster_change();
	tests_run++;
	if(result == 0){
		tests_passed++;
	}

	printf("\nRan %i test(s), %i test(s) passed\n", tests_run, tests_passed);
}

