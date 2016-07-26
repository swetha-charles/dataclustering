#include "hough_header.h"
#include "CuTest.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void check_variance(CuTest *tc){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->variance_of_data;

	double expected = 0.005;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);



}

void check_ca(CuTest *tc){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->ca;

	double expected = 0.9;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);



}

void check_cr(CuTest *tc){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->cr;

	double expected = 0.9;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);



}

void check_w1(CuTest *tc){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->w1;

	double expected = 1.9;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

void check_w2(CuTest *tc){
	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	double actual = prior_parameters->w2;

	double expected = 2.0;
	CuAssertDblEquals(tc,  expected, actual, 0.0001);

}

CuSuite* prior_parameters_get_suite() {
        CuSuite* suite = CuSuiteNew();
        SUITE_ADD_TEST(suite, check_variance);
        SUITE_ADD_TEST(suite, check_ca);
        SUITE_ADD_TEST(suite, check_cr);
        SUITE_ADD_TEST(suite, check_w1);
        SUITE_ADD_TEST(suite, check_w2);
       
        return suite;
    }
