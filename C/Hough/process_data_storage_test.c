#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"

int test_storage_p_r_alpha_given_x_equation_1(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//   alpha: -7.853982e-01, al_i 1, r: 2.000000e-01, r_i: 5, p: 2.641841e-182
	// x1: 1.106309e-01, x2: 5.183355e-02, sigma: 5.000000e-03
	double p_x = get_p_x(1.106309e-01, 5.183355e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x(1.106309e-01, 5.183355e-02, 0.005, p_x, ht_results, alphas_and_radii, priors, data);
	
	double actual = ht_results->p_r_alpha_given_x[((4) * alphas_and_radii->no_of_alphas) + (0)];
	double expected =  2.641841e-182;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

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


int test_storage_p_r_alpha_given_x_equation_2(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//    alpha: -6.853982e-01, al_i 3, r: 1.000000e-01, r_i: 3, p: 1.071577e-70
 	//x1: 8.674737e-02, x2: 4.329859e-02, sigma: 5.000000e-03
	double p_x = get_p_x(8.674737e-02, 4.329859e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x(8.674737e-02, 4.329859e-02, 0.005, p_x, ht_results, alphas_and_radii, priors, data);
	
	double actual = ht_results->p_r_alpha_given_x[((2)  * alphas_and_radii->no_of_alphas) + (2)];
	double expected =  1.071577e-70;


	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 2\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 2\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}


int test_storage_p_r_alpha_given_x_cumulative_1(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//    alpha: -6.853982e-01, al_i 3, r: 1.000000e-01, r_i: 3, p: 1.071577e-70
 	//x1: 8.674737e-02, x2: 4.329859e-02, sigma: 5.000000e-03
	double p_x_1 = get_p_x(8.674737e-02, 4.329859e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x(8.674737e-02, 4.329859e-02, 0.005, p_x_1, ht_results, alphas_and_radii, priors, data);


	//    alpha: -6.853982e-01, al_i 3, r: 1.000000e-01, r_i: 3, p: 1.071577e-70
 	//x1: 8.674737e-02, x2: 4.329859e-02, sigma: 5.000000e-03
	double p_x = get_p_x(8.674737e-02, 4.329859e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x(8.674737e-02, 4.329859e-02, 0.005, p_x, ht_results, alphas_and_radii, priors, data);


	
	double actual = (ht_results->p_r_alpha_given_data[((2)  * alphas_and_radii->no_of_alphas) + (2)]);
	double expected =  ((1.071577e-70)/100)+ ((1.071577e-70)/100);


	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 3\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 3\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}


int test_storage_p_r_alpha_given_x_cumulative_2(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	// alpha: -7.853982e-01, al_i 1, r: 2.000000e-01, r_i: 5, p: 1.942384e-203
 	//x1: 1.824756e-01, x2: -3.470703e-01, sigma: 5.000000e-03
	double p_x_1 = get_p_x(1.824756e-01, -3.470703e-01,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x(1.824756e-01, -3.470703e-01, 0.005, p_x_1, ht_results, alphas_and_radii, priors, data);


	//    alpha: -7.853982e-01, al_i 1, r: 2.000000e-01, r_i: 5, p: 8.459731e-230
	// x1: -8.844558e-02, x2: -4.334480e-02, sigma: 5.000000e-03
	double p_x_2 = get_p_x(-8.844558e-02, -4.334480e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x(-8.844558e-02, -4.334480e-02, 0.005, p_x_2, ht_results, alphas_and_radii, priors, data);


	
	double actual = (ht_results->p_r_alpha_given_data[((4)  * alphas_and_radii->no_of_alphas) + (0)]);
	double expected =  (( 1.942384e-203)/100)+ ((8.459731e-230)/100);


	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 4\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 4\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}


int test_storage_p_alpha_given_x_1(){
	// with one data point

	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);
	int no_of_alphas = alphas_and_radii->no_of_alphas;

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	// al_i 1, p: 2.894727e-19
	//// al_i 99, p: 2.882849e-16
 	//x1: 2.688487e-02, x2: -9.261371e-02, sigma: 5.000000e-03
	double p_x_1 = get_p_x( 2.688487e-02,-9.261371e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x( 2.688487e-02, -9.261371e-02, 0.005, p_x_1, ht_results, alphas_and_radii, priors, data);

	get_p_alpha_given_x(0, ht_results, alphas_and_radii);
	
	
	double actual = (ht_results->p_alpha_given_data[((0)  * (no_of_alphas)) + (98)]);
	double expected =  2.882849e-16;


	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 5\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 5\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}

int test_storage_p_alpha_given_x_2(){
	// with one data point

	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);
	int no_of_alphas = alphas_and_radii->no_of_alphas;

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	// al_i 1, p: 2.894727e-19
	//// al_i 99, p: 2.882849e-16
 	//x1: 2.688487e-02, x2: -9.261371e-02, sigma: 5.000000e-03
	double p_x_1 = get_p_x( 2.688487e-02,-9.261371e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x( 2.688487e-02, -9.261371e-02, 0.005, p_x_1, ht_results, alphas_and_radii, priors, data);

	get_p_alpha_given_x(0, ht_results, alphas_and_radii);
	

	// x1: -3.286673e-02, x2: -4.077785e-02, sigma: 5.000000e-03
	// alpha: 5.464602e+00, al_i 99, p: 2.149240e+00

	double p_x_2 = get_p_x(  -3.286673e-02,-4.077785e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x( -3.286673e-02, -4.077785e-02, 0.005, p_x_2, ht_results, alphas_and_radii, priors, data);

	get_p_alpha_given_x(1, ht_results, alphas_and_radii);
	
	double actual = (ht_results->p_alpha_given_data[((1)  * (no_of_alphas)) + (98)]);
	double expected =  2.149240e+00;


	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 6\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 6\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}

int print_radius_array(struct alphas_and_radii *alphas_and_radii){
	printf("Printing the radius array\n" );
	int i; int j;
	for(i =0; i < alphas_and_radii->no_of_alphas; i++){
		for(j = 0; j < alphas_and_radii->no_of_radii; j++){
			printf("alpha: %i, alpha: %f, radius: %i, radius %f, \n",i , alphas_and_radii->alpha_array_pointer[i], j, alphas_and_radii->radius_array_pointer[j]);
		   
		}
	}





	return 0;
}

void print_p_alpha_given_data(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);
	int no_of_alphas = alphas_and_radii->no_of_alphas;

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	// al_i 1, p: 2.894727e-19
	//// al_i 99, p: 2.882849e-16
 	//x1: 2.688487e-02, x2: -9.261371e-02, sigma: 5.000000e-03
	double p_x_1 = get_p_x( 2.688487e-02,-9.261371e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x( 2.688487e-02, -9.261371e-02, 0.005, p_x_1, ht_results, alphas_and_radii, priors, data);

	get_p_alpha_given_x(0, ht_results, alphas_and_radii);
	
	//print p_r_alpha_|_x
	int i, j;

	// for(i =0; i < alphas_and_radii->no_of_alphas; i++){
	// 	for(j = 0; j < alphas_and_radii->no_of_radii; j++){
	// 	printf("alpha: %i, alpha_val %f, radius: %i, radius_val: %f, p_r_alpha_given_x %e\n", i,alphas_and_radii->alpha_array_pointer[i],j,alphas_and_radii->radius_array_pointer[j],ht_results->p_r_alpha_given_x[ (i * alphas_and_radii->no_of_alphas) + j ]);
		   
	// 	}
	// }

	

	for(i = 0; i < 2; i ++){
		for(j = 0; j < no_of_alphas; j++){
			printf("%e\n", ht_results->p_alpha_given_data[(i * no_of_alphas) + j]);
		}
		printf("New index\n");
	}



	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);
}

int main(int argc, char const *argv[])
{

	int total_test = 0;
	int passed_tests = 0;
	

	passed_tests += test_storage_p_r_alpha_given_x_equation_1();
	printf("\n");
	total_test++;	
	passed_tests += test_storage_p_r_alpha_given_x_equation_2();
	printf("\n");
	total_test++;
	passed_tests += test_storage_p_r_alpha_given_x_cumulative_1();
	printf("\n");
	total_test++;
	passed_tests += test_storage_p_r_alpha_given_x_cumulative_2();
	printf("\n");
	total_test++;
	passed_tests += test_storage_p_alpha_given_x_1();
	printf("\n");
	total_test++;
	passed_tests += test_storage_p_alpha_given_x_2();
	printf("\n");
	total_test++;

	//print_p_alpha_given_data();
	// print_priors();


	printf("\nTotal tests run: %i, passed: %i\n", total_test, passed_tests );
	return 0;
}