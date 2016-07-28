#include "hough_header.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int check_variance(){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->variance_of_data;

	double expected = 0.005;
	destroy_prior_parameters(prior_parameters);
	
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

int check_ca(){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->ca;

	double expected = 0.9;
	destroy_prior_parameters(prior_parameters);
	
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

int check_cr(){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->cr;

	double expected = 0.9;
	destroy_prior_parameters(prior_parameters);
	
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

int check_w1(){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->w1;

	double expected = 1.9;
	destroy_prior_parameters(prior_parameters);
	
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

int check_w2(){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->w2;

	double expected = 2.0;
	destroy_prior_parameters(prior_parameters);
	
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
int main(int argc, char const *argv[])
{
	int total_test = 0;
	int passed_tests = 0;

	passed_tests += check_variance();
	printf("\n");
	total_test++;

	passed_tests += check_ca();
	printf("\n");
	total_test++;

	passed_tests += check_cr();
	printf("\n");
	total_test++;

	passed_tests += check_w1();
	printf("\n");
	total_test++;

	passed_tests += check_w2();
	printf("\n");
	total_test++;




	printf("\nTotal tests run: %i, passed: %i\n", total_test, passed_tests );

	
	return 0;
}