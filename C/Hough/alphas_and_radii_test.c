#include "hough_header.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int test_initial_a(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(1, 1);

	double actual = alphas_and_radii->alpha_array_pointer[0];
	
	double expected = 0;
	
	destroy_alphas_and_radii(alphas_and_radii);	

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

int test_initial_r(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(1, 1);

	
	double actual = alphas_and_radii->radius_array_pointer[0];

	double expected = 0;

	destroy_alphas_and_radii(alphas_and_radii);

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

int test_middle_a(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->alpha_array_pointer[5];

	double expected = (5*0.05);

	destroy_alphas_and_radii(alphas_and_radii);

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


int test_middle_r(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	
	double actual = alphas_and_radii->radius_array_pointer[5];

	double expected = 5*0.05;

	destroy_alphas_and_radii(alphas_and_radii);

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

int test_end_a(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	//true number of alphas is last_index + 1
	int last_index = (2*pi)/0.05;
	double actual = alphas_and_radii->alpha_array_pointer[last_index];
	double expected = (last_index * 0.05);
	destroy_alphas_and_radii(alphas_and_radii);

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

int test_end_r(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	//true number of r is last_index + 1
	int last_index = 3/0.05;
	double actual = alphas_and_radii->radius_array_pointer[last_index];
	double expected = (last_index * 0.05);

	destroy_alphas_and_radii(alphas_and_radii);

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

int test_no_a(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->no_of_alphas;
	double expected = ((2 * pi )/0.05) + 1;

	destroy_alphas_and_radii(alphas_and_radii);

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

int test_no_r(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->no_of_radii;
	double expected = ((3 / 0.05)+1);

	destroy_alphas_and_radii(alphas_and_radii);

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

int test_dr(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->dr;
	double expected = 0.05;

	destroy_alphas_and_radii(alphas_and_radii);

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

int test_da(int test_no){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->da;
	double expected = 0.05;

	destroy_alphas_and_radii(alphas_and_radii);

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
	passed_tests += test_initial_r(total_test);
	printf("\n");
	
	total_test++;
	passed_tests += test_initial_a(total_test);
	printf("\n");
	

	total_test++;
	passed_tests += test_middle_a(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_middle_r(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_end_a(total_test);
	printf("\n");
	
	total_test++;
	passed_tests += test_end_r(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_no_a(total_test);
	printf("\n");
	
	total_test++;
	passed_tests += test_no_r(total_test);
	printf("\n");
	
	total_test++;
	passed_tests += test_da(total_test);
	printf("\n");
	
	total_test++;
	passed_tests += test_dr(total_test);
	printf("\n");
	

	printf("\nTotal tests run: %i, passed: %i\n", total_test, passed_tests );

	return 0;
}