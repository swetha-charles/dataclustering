#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"

int  test_priors_alpha_storage_1()
{	
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	calculate_priors(alphas_and_radii, prior_parameters, priors);
	int i = 27;
	double expected = calculate_p_alpha( (-pi/4) + (0.05 * i), 0.9);
	double actual = priors->p_alpha[27];
	

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(expected == actual){
		printf("Passed test 1\n");

		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 2\n");

		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 0;
	}
	return 0;
}

int  test_priors_alpha_storage_2()
{	
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	calculate_priors(alphas_and_radii, prior_parameters, priors);
	int i = 100;
	double expected = calculate_p_alpha( (-pi/4) + (0.05 * i), 0.9);
	double actual = priors->p_alpha[100];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(expected == actual){
		printf("Passed test 2\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 1;
	} else {
		printf("Failed test 2\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);

		return 0;

	}
	
}

int test_priors_p_r_given_alpha_storage_1(){
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
	// printf("alpha: %f\n", alpha);
	// printf("radius: %f\n", radius);


	double expected = calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->p_r_given_alpha[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(expected == actual){
		printf("Passed test 3\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 1;
	} else {
		printf("Failed test 3\n");
		printf("Expected: %f\n", expected);
		printf("Actual: %f\n", actual);
		return 0;
	}
}

int test_priors_p_r_given_alpha_storage_2(){
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
	// printf("alpha: %f\n", alpha);
	// printf("radius: %f\n", radius);


	double expected = calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->p_r_given_alpha[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(expected == actual){
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


int test_total_priors_1(){
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
	// printf("alpha: %f\n", alpha);
	// printf("radius: %f\n", radius);


	double expected = calculate_p_alpha(alpha, 0.9)*calculate_prior_r_given_alpha(radius,alpha,  prior_parameters->cr, prior_parameters->w1, prior_parameters->w2);
	double actual = priors->total_prior[(radius_i * alphas_and_radii->no_of_alphas) + alpha_i];

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

	if(expected == actual){
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

int main(int argc, char const *argv[])
{

	int total_test = 5;
	int passed_tests = 0;
	passed_tests += test_priors_alpha_storage_1();
	printf("\n");
	passed_tests += test_priors_alpha_storage_2();
	printf("\n");
	passed_tests +=  test_priors_p_r_given_alpha_storage_1();
	printf("\n");
	passed_tests +=  test_priors_p_r_given_alpha_storage_2();
	printf("\n");
	passed_tests +=  test_total_priors_1();
	printf("\n");


	printf("\nTotal tests run: %i, passed: %i\n", total_test, passed_tests );
	return 0;
}


//Gene Ontology in R is easier - R package gene ontology, Python (modules / libraries)
//compare your algorithm your benchmark 

//Check your algorithm with the older version to test 
