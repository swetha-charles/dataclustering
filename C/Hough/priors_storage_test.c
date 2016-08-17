#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"

/*
 * This class is used to test that the storage of p(a), p(r | a) and p(r, a) matches the result of the equations
 */
int  test_priors_alpha_storage_1(int test_no)
{	
	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	int i = 27;
	double expected = calculate_p_alpha(0.05 * i, 0.9);
	double actual = priors->p_alpha[27];
	
	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

		if(abs(expected - actual) < 0.00001){
		printf("Passed test %i\n", test_no);
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test %i\n", test_no);
		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}

}

int  test_priors_alpha_storage_2(int test_no)
{	
	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);
	
	int i = 100;
	double expected = calculate_p_alpha((0.05 * i), 0.9);
	double actual = priors->p_alpha[100];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(abs(expected - actual) < 0.00001){
		printf("Passed test %i\n", test_no);
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test %i\n", test_no);
		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}

	
}

int test_priors_p_r_given_alpha_storage_1(int test_no){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	int alpha_i = 100;
	int radius_i = 40;
	double alpha = alphas_and_radii->alpha_array_pointer[alpha_i];
	double radius = alphas_and_radii->radius_array_pointer[radius_i];

	double expected = calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->p_r_given_alpha[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(abs(expected - actual) < 0.00001){
		printf("Passed test %i\n", test_no);
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test %i\n", test_no);
		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}

}

int test_priors_p_r_given_alpha_storage_2(int test_no){
	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	int alpha_i = 125;
	int radius_i = 59;
	double alpha = alphas_and_radii->alpha_array_pointer[alpha_i];
	double radius = alphas_and_radii->radius_array_pointer[radius_i];

	double expected = calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->p_r_given_alpha[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(abs(expected - actual) < 0.00001){
		printf("Passed test %i\n", test_no);
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test %i\n", test_no);
		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}

}


int test_total_priors_1(int test_no){

	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	calculate_priors(alphas_and_radii, prior_parameters, priors);
	int alpha_i = 125;
	int radius_i = 59;
	double alpha = alphas_and_radii->alpha_array_pointer[alpha_i];
	double radius = alphas_and_radii->radius_array_pointer[radius_i];

	double expected = calculate_p_alpha(alpha, 0.9)*calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->total_prior[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(abs(expected - actual) < 0.00001){
		printf("Passed test %i\n", test_no);
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test %i\n", test_no);
		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}

}

int test_total_priors_2(int test_no){

	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	calculate_priors(alphas_and_radii, prior_parameters, priors);
	int alpha_i = 0;
	int radius_i = 0;
	double alpha = alphas_and_radii->alpha_array_pointer[alpha_i];
	double radius = alphas_and_radii->radius_array_pointer[radius_i];

	double expected = calculate_p_alpha(alpha, 0.9)*calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->total_prior[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(abs(expected - actual) < 0.00001){
		printf("Passed test %i\n", test_no);
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test %i\n", test_no);
		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}

}

int test_total_priors_3(int test_no){

	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	calculate_priors(alphas_and_radii, prior_parameters, priors);
	int alpha_i = 70;
	int radius_i = 30;
	double alpha = alphas_and_radii->alpha_array_pointer[alpha_i];
	double radius = alphas_and_radii->radius_array_pointer[radius_i];

	double expected = calculate_p_alpha(alpha, 0.9)*calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->total_prior[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(abs(expected - actual) < 0.00001){
		printf("Passed test %i\n", test_no);
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test %i\n", test_no);
		printf("Expected: %e\n", expected);
		printf("Actual: %.e\n", actual);

		return 0;
	}

}

int main(int argc, char const *argv[])
{

	int total_test = 0;
	int passed_tests = 0;
	
	total_test++;
	passed_tests += test_priors_alpha_storage_1(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_priors_alpha_storage_2(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_priors_p_r_given_alpha_storage_1(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_priors_p_r_given_alpha_storage_2(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_total_priors_1(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_total_priors_2(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_total_priors_3(total_test);
	printf("\n");

	printf("\nTotal tests run: %i, passed: %i\n", total_test, passed_tests );
	return 0;
}


//Gene Ontology in R is easier - R package gene ontology, Python (modules / libraries)
//compare your algorithm your benchmark 

//Check your algorithm with the older version to test 
