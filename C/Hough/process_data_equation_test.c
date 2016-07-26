#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"

int test_p_x_given_alpha_r_1(){

	double actual = p_x_given_alpha_r(5, 5, 5, 5, 5);
	double expected = 0.000540;

	
	if(abs(expected - actual) < 0.00001){
		printf("Passed test 1\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 1\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}
}

int test_p_x_given_alpha_r_2(){

	double actual = p_x_given_alpha_r( -0.5053875, 0.6011689, 2.214602,0.7500000, 0.005);
	double expected = 2.116404E-14;
	
	if(((expected - actual < 0.00001) && expected>=actual) || ((actual - expected  < 0.00001) && actual>=expected)){
		printf("Passed test 2\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 2\n");
		printf("difference : %e\n", expected - actual);
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}

int test_p_x_given_alpha_r_3(){

	double actual = p_x_given_alpha_r( -0.5053875, 0.6011689, 2.214602,0.6500000, 0.005);
	double expected = 4.524702E-58;
	
	if(((expected - actual < 0.00001) && expected>=actual) || ((actual - expected  < 0.00001) && actual>=expected)){
		printf("Passed test 3\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 3\n");
		printf("difference : %e\n", expected - actual);
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}



int test_get_p_x_1(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);


	double actual = get_p_x(6.007276E-03, 1.416331E-03, 0.005, alphas_and_radii, priors);
	double expected =  3.959956E1;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 4\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 4\n");

		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 0;
	}
}



int test_get_p_x_2(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);
	//x 10
	double actual = get_p_x(-8.718867e-02, -1.630213e-01, 0.005, alphas_and_radii, priors);
	double expected =  2.600512e-02;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 5\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 5\n");

		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 0;
	}
}

int test_get_p_x_3(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	// 52 x1: -4.122377e-02, x2: 1.018349e-01, sigma: 5.000000e-03p_x is 7.547865e-01
	double actual = get_p_x(-4.122377e-02, 1.018349e-01, 0.005, alphas_and_radii, priors);
	double expected =  7.547865e-01;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 6\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 6\n");

		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 0;
	}
}

int test_get_p_x_4(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	// 115 x1: 3.506747e-01, x2: -2.619796e-01, sigma: 5.000000e-03p_x is 1.574572e-01
	double actual = get_p_x(3.506747e-01,  -2.619796e-01, 0.005, alphas_and_radii, priors);
	double expected =  1.574572e-01;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 7\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 7\n");

		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 0;
	}
}

int test_get_p_r_alpha_given_x_equation_1(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//  alpha: 5.464602e+00, al_i 126, r: 1.000000e-01, r_i: 3, p: 1.412802e-259
	// x1: 8.051829e-02, x2: 1.330519e-01,
	double p_x = get_p_x(8.051829e-02, 1.330519e-01,0.005, alphas_and_radii, priors);
	double actual = calculate_p_r_alpha_given_x(8.051829e-02, 1.330519e-01, 0.005, 5.464602e+00, 1.000000e-01, p_x, alphas_and_radii, priors, 125, 2);
	double expected =  1.412802e-259;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 8\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 8\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}

int test_get_p_r_alpha_given_x_equation_2(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//   alpha: -7.853982e-01, al_i 1, r: 2.000000e-01, r_i: 5, p: 2.641841e-182
	// x1: 1.106309e-01, x2: 5.183355e-02, sigma: 5.000000e-03
	double p_x = get_p_x(1.106309e-01, 5.183355e-02,0.005, alphas_and_radii, priors);
	double actual = calculate_p_r_alpha_given_x(1.106309e-01, 5.183355e-02, 0.005, -7.853982e-01, 2.000000e-01, p_x, alphas_and_radii, priors, 0, 4);
	double expected =  2.641841e-182;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 9\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 9\n");

		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}

int test_get_p_x_5(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

 	//x1: -1.365667e-01, x2: 2.263933e-01, sigma: 5.000000e-03
	//p_x is 1.479164e-01
	double actual = get_p_x(-1.365667e-01,  2.263933e-01, 0.005, alphas_and_radii, priors);
	double expected =  1.479164e-01;

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(((expected - actual < 0.001) && expected>=actual) || ((actual - expected  < 0.001) && actual>=expected)){
		printf("Passed test 8\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 8\n");

		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 0;
	}
}


// int print_priors(){
// 	struct priors *priors;

// 	struct alphas_and_radii *alphas_and_radii;
// 	struct prior_parameters *prior_parameters;
// 	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	
// 	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
// 	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
// 	calculate_priors(alphas_and_radii, prior_parameters, priors);

// 	int i =0;
// 	int j = 0;
// 	int priors_greater_than_0 = 0;
	
// 	for(; i < alphas_and_radii->no_of_alphas; i++){
// 		double alpha = alphas_and_radii->alpha_array_pointer[i];

// 		for(j = 0; j < alphas_and_radii->no_of_radii; j++){
// 			double r = alphas_and_radii->radius_array_pointer[j];
// 			//prior is p(a, r)
// 			printf(" alpha: %f, radius: %f, total prior: %e\n", alpha, r, priors->total_prior[(j * alphas_and_radii->no_of_alphas) + i]);	
// 			printf(" alpha: %f, radius: %f, p_r_given_alpha: %e\n", alpha, r, priors->p_r_given_alpha[(j * alphas_and_radii->no_of_alphas) + i]);	
// 			printf(" alpha: %f, radius: %f, p_alpha: %e\n", alpha, r, priors->p_alpha[(j * alphas_and_radii->no_of_alphas) + i]);	
// 			if(priors->total_prior[(j * alphas_and_radii->no_of_alphas) + i] > 0){
// 				priors_greater_than_0++;
// 			}	
// 		}
// 	}
// 	printf("Number of priors greater than 0 are: %i\n", priors_greater_than_0);
// 	return 1;
// }

int print_p_r_alpha_given_x(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 5);

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//   alpha: -7.853982e-01, al_i 1, r: 2.000000e-01, r_i: 5, p: 2.641841e-182 
	// x1: 1.106309e-01, x2: 5.183355e-02, sigma: 5.000000e-03
	double p_x = get_p_x(1.106309e-01, 5.183355e-02,0.005, alphas_and_radii, priors);
	
	get_p_r_alpha_given_x(1.106309e-01, 5.183355e-02, 0.005, p_x, ht_results, alphas_and_radii, priors, data);
	
	int i; int j;

	for(i =0; i < alphas_and_radii->no_of_alphas; i++){
		for(j = 0; j < alphas_and_radii->no_of_radii; j++){
		printf("alpha: %i, alpha_val %f, radius: %i, radius_val: %f, p_r_alpha_given_x %e\n", i,alphas_and_radii->alpha_array_pointer[i],j,alphas_and_radii->radius_array_pointer[j],ht_results->p_r_alpha_given_x[ (i * alphas_and_radii->no_of_alphas) + j ]);
		   
		}
	}




	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

	return 0;
}


int test_p_x_given_alpha_r_4(){


	//x1 : -3.510317e+00, x2 -1.815205e+00
	/*variance: 0.005000, alpha: 42, r: 1
	alpha: 1.314602, r: 0.050000
	x1: -3.510317, x2: -1.815205, var: 0.005000
	matrix result: 5.986583e+05
	final result: 0.000000e+00
	noise model: 0.000000e+00 priors: 6.260164e-02*/

	FILE* file = fopen("debug_test.txt", "w");
	double actual = p_x_given_alpha_r_debug( -3.510317e+00, -1.815205e+00, 1.314602,0.050000, 0.005, file);
	double expected = 8.361133e-156;
	
	if(((expected - actual < 0.00001) && expected>=actual) || ((actual - expected  < 0.00001) && actual>=expected)){
		printf("Passed test 3\n");
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);
		return 1;
	} else {
		printf("Failed test 3\n");
		printf("difference : %e\n", expected - actual);
		printf("Expected: %e\n", expected);
		printf("Actual: %e\n", actual);

		return 0;
	}
}

int print_radius_array(){

	
	struct alphas_and_radii *alphas_and_radii;

	
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	printf("Printing the radius array\n" );
	int i; int j;
	for(i =0; i < alphas_and_radii->no_of_alphas; i++){
		for(j = 0; j < alphas_and_radii->no_of_radii; j++){
			printf("alpha: %i, alpha: %f, radius: %i, radius %f, \n",i , alphas_and_radii->alpha_array_pointer[i], j, alphas_and_radii->radius_array_pointer[j]);
		   
		}
	}





	return 0;
}

// int print_radius_array_after_p_x(){

	
// 	struct priors *priors;

// 	struct prior_parameters *prior_parameters;
// 	struct alphas_and_radii *alphas_and_radii;

// 	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
// 	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
// 	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
// 	calculate_priors(alphas_and_radii, prior_parameters, priors);

// 	// 115 x1: 3.506747e-01, x2: -2.619796e-01, sigma: 5.000000e-03p_x is 1.574572e-01
// 	get_p_x(3.506747e-01,  -2.619796e-01, 0.005, alphas_and_radii, priors);

// 	printf("Printing the radius array\n" );
// 	int i; int j;
// 	for(i =0; i < alphas_and_radii->no_of_alphas; i++){
// 		for(j = 0; j < alphas_and_radii->no_of_radii; j++){
// 			printf("alpha: %i, alpha: %f, radius: %i, radius %f, \n",i , alphas_and_radii->alpha_array_pointer[i], j, alphas_and_radii->radius_array_pointer[j]);
		   
// 		}
// 	}


// 	destroy_prior_parameters(prior_parameters);
// 	destroy_alphas_and_radii(alphas_and_radii);
// 	destroy_priors(priors);

// 	return 0;
// }

int main(int argc, char const *argv[])
{

	int total_test = 0;
	int passed_tests = 0;
	// passed_tests += test_p_x_given_alpha_r_1();
	// printf("\n");
	// total_test++;
	// passed_tests += test_p_x_given_alpha_r_2();
	// printf("\n");
	// total_test++;
	// passed_tests += test_p_x_given_alpha_r_3();
	// printf("\n");
	// total_test++;
	// passed_tests += test_get_p_x_1();
	// printf("\n");
	// total_test++;
	// passed_tests += test_get_p_x_2();
	// printf("\n");
	// total_test++;
	// passed_tests += test_get_p_x_3();
	// printf("\n");
	// total_test++;
	// passed_tests += test_get_p_x_4();
	// printf("\n");
	// total_test++;
	// passed_tests += test_get_p_r_alpha_given_x_equation_1();
	// printf("\n");
	// total_test++;
	// passed_tests += test_get_p_r_alpha_given_x_equation_2();
	// printf("\n");
	// total_test++;

	passed_tests += test_get_p_x_5();
	printf("\n");
	total_test++;

	// passed_tests += test_p_x_given_alpha_r_4();
	// printf("\n");
	// total_test++;



	// print_priors();


	printf("\nTotal tests run: %i, passed: %i\n", total_test, passed_tests );
	return 0;
}