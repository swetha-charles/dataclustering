#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "hough_header.h"
#include "CuTest.h"



/////////////Test the basic prior equations//////////

void test_calculate_p_alpha_1(CuTest *tc){
	double actual = calculate_p_alpha(0, 0.9);

	double expected = 0.1591;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_alpha_2(CuTest *tc){
	double actual = calculate_p_alpha(-0.700, 0.9);

	double expected = 0.16662;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_alpha_3(CuTest *tc){
	double actual = calculate_p_alpha(0.600, 0.9);

	double expected = 0.15276;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_alpha_4(CuTest *tc){
	double actual = calculate_p_alpha(2.00, 0.9);

	double expected = 0.1637;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_alpha_5(CuTest *tc){
	double actual = calculate_p_alpha(3.80, 0.9);

	double expected = 0.1521;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_alpha_6(CuTest *tc){
	double actual = calculate_p_alpha(4.00, 0.9);

	double expected = 0.151557;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_r_given_alpha_1(CuTest *tc){
	double actual = calculate_prior_r_given_alpha(0.5, 0, 0.9, 1.9, 2.0);

	double expected = 0.3876;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_r_given_alpha_2(CuTest *tc){
	double actual = calculate_prior_r_given_alpha(0.5, -.700, 0.9, 1.9, 2.0);

	double expected = 0.3868;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_r_given_alpha_3(CuTest *tc){
	double actual = calculate_prior_r_given_alpha(0.5, 0.600, 0.9, 1.9, 2.0);

	double expected = 0.3883;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_r_given_alpha_4(CuTest *tc){
	double actual = calculate_prior_r_given_alpha(0.5, 2.00, 0.9, 1.9, 2.0);

	double expected = 0.3871;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_r_given_alpha_5(CuTest *tc){
	double actual = calculate_prior_r_given_alpha(0.5, 3.00, 0.9, 1.9, 2.0);

	double expected = 0.3874;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void test_calculate_p_r_given_alpha_6(CuTest *tc){
	double actual = calculate_prior_r_given_alpha(0.5, 4.00, 0.9, 1.9, 2.0);

	double expected = 0.3885;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}


CuSuite* prior_parameters_get_suite() {
        CuSuite* suite = CuSuiteNew();

      //  SUITE_ADD_TEST(suite, setup);
        SUITE_ADD_TEST(suite, test_calculate_p_alpha_1);
      	SUITE_ADD_TEST(suite, test_calculate_p_alpha_2);
      	SUITE_ADD_TEST(suite, test_calculate_p_alpha_3);
      	SUITE_ADD_TEST(suite, test_calculate_p_alpha_4);
      	SUITE_ADD_TEST(suite, test_calculate_p_alpha_5);
      	SUITE_ADD_TEST(suite, test_calculate_p_alpha_6);

		SUITE_ADD_TEST(suite, test_calculate_p_r_given_alpha_1);
		SUITE_ADD_TEST(suite, test_calculate_p_r_given_alpha_2);
		SUITE_ADD_TEST(suite, test_calculate_p_r_given_alpha_3);
		SUITE_ADD_TEST(suite, test_calculate_p_r_given_alpha_4);
		SUITE_ADD_TEST(suite, test_calculate_p_r_given_alpha_5);
		SUITE_ADD_TEST(suite, test_calculate_p_r_given_alpha_6);


        return suite;
    }
