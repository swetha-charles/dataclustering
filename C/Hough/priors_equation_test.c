#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "hough_header.h"



/////////////Test the basic prior equations//////////

int test_calculate_p_alpha_1(int test_no){
	double actual = calculate_p_alpha(0, 0.9);

	double expected = 0.1591;

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

int test_calculate_p_alpha_2(int test_no){
	double actual = calculate_p_alpha(-0.700, 0.9);

	double expected = 0.16662;
	
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

int test_calculate_p_alpha_3(int test_no){
	double actual = calculate_p_alpha(0.600, 0.9);

	double expected = 0.15276;

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

int test_calculate_p_alpha_4(int test_no){
	double actual = calculate_p_alpha(2.00, 0.9);

	double expected = 0.1637;

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

int test_calculate_p_alpha_5(int test_no){
	double actual = calculate_p_alpha(3.80, 0.9);

	double expected = 0.1521;
	
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

int test_calculate_p_alpha_6(int test_no){
	double actual = calculate_p_alpha(4.00, 0.9);

	double expected = 0.151557;

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

int test_calculate_p_r_given_alpha_1(int test_no){
	double actual = calculate_prior_r_given_alpha(0.5, 0, 0.9, 1.9, 2.0);

	double expected = 0.3876;

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

int test_calculate_p_r_given_alpha_2(int test_no){
	double actual = calculate_prior_r_given_alpha(0.5, -.700, 0.9, 1.9, 2.0);

	double expected = 0.3868;

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

int test_calculate_p_r_given_alpha_3(int test_no){
	double actual = calculate_prior_r_given_alpha(0.5, 0.600, 0.9, 1.9, 2.0);

	double expected = 0.3883;

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

int test_calculate_p_r_given_alpha_4(int test_no){
	double actual = calculate_prior_r_given_alpha(0.5, 2.00, 0.9, 1.9, 2.0);

	double expected = 0.3871;

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

int test_calculate_p_r_given_alpha_5(int test_no){
	double actual = calculate_prior_r_given_alpha(0.5, 3.00, 0.9, 1.9, 2.0);

	double expected = 0.3874;

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

int test_calculate_p_r_given_alpha_6(int test_no){
	double actual = calculate_prior_r_given_alpha(0.5, 4.00, 0.9, 1.9, 2.0);

	double expected = 0.3885;

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
	passed_tests += test_calculate_p_alpha_1(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_alpha_2(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_alpha_3(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_alpha_4(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_alpha_5(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_alpha_6(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_r_given_alpha_1(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_r_given_alpha_2(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_r_given_alpha_3(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_r_given_alpha_4(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_r_given_alpha_5(total_test);
	printf("\n");

	total_test++;
	passed_tests += test_calculate_p_r_given_alpha_6(total_test);
	printf("\n");

	
	return 0;
}