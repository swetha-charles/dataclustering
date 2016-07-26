#include "hough_header.h"
#include "CuTest.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_create_alphas_and_radii_initial_a(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(1, 1);

	double actual_alpha = alphas_and_radii->alpha_array_pointer[0];
	
	double expected_alpha = -0.785;
	

	CuAssertDblEquals(tc,  expected_alpha, actual_alpha, 0.05);
	//CuAssertDblEquals(tc, actual_radius, expected_radius, 0.05);

	destroy_alphas_and_radii(alphas_and_radii);


}

void test_create_alphas_and_radii_initial_r(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(1, 1);

	
	double actual_radius = alphas_and_radii->radius_array_pointer[0];

	double expected_radius = 0;

	//CuAssertDblEquals(tc, actual_alpha, expected_alpha, 0.05);
	CuAssertDblEquals(tc, expected_radius, actual_radius, 0.05);

	destroy_alphas_and_radii(alphas_and_radii);


}

void test_create_alphas_and_radii_middle_a(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual_alpha = alphas_and_radii->alpha_array_pointer[5];

	double expected_alpha = -0.535;


	CuAssertDblEquals(tc,  expected_alpha, actual_alpha, 0.01);
	//CuAssertDblEquals(tc, actual_radius, expected_radius, 0.01);

	destroy_alphas_and_radii(alphas_and_radii);
}


void test_create_alphas_and_radii_middle_r(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	
	double actual_radius = alphas_and_radii->radius_array_pointer[5];

	double expected_radius = 0.25;

	//CuAssertDblEquals(tc, actual_alpha, expected_alpha, 0.01);
	CuAssertDblEquals(tc,  expected_radius, actual_radius, 0.01);

	destroy_alphas_and_radii(alphas_and_radii);
}

void test_create_alphas_and_radii_end_a(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	

	double actual_alpha = alphas_and_radii->alpha_array_pointer[125];
	double expected_alpha = 5.498;

	CuAssertDblEquals(tc,  expected_alpha, actual_alpha, 0.01);
//	CuAssertDblEquals(tc, actual_radius, expected_radius, 0.01);

	destroy_alphas_and_radii(alphas_and_radii);
}

void test_create_alphas_and_radii_end_r(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual_radius = alphas_and_radii->radius_array_pointer[60];
	double expected_radius = 3;



//	CuAssertDblEquals(tc, actual_alpha, expected_alpha, 0.01);
	CuAssertDblEquals(tc,  expected_radius,actual_radius, 0.01);

	destroy_alphas_and_radii(alphas_and_radii);
}

void test_attr_a(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->no_of_alphas;
	double expected = 126;

	CuAssertDblEquals(tc,  expected,actual, 0.01);
	destroy_alphas_and_radii(alphas_and_radii);
}

void test_attr_r(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->no_of_radii;
	double expected = 61;

	CuAssertDblEquals(tc,  expected,actual, 0.01);
	destroy_alphas_and_radii(alphas_and_radii);
}

void test_attr_dr(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->dr;
	double expected = 0.05;

	CuAssertDblEquals(tc,  expected,actual, 0.01);
	destroy_alphas_and_radii(alphas_and_radii);
}

void test_attr_da(CuTest *tc){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	double actual = alphas_and_radii->da;
	double expected = 0.05;

	CuAssertDblEquals(tc,  expected,actual, 0.01);
	destroy_alphas_and_radii(alphas_and_radii);
}







 CuSuite* alpha_radii_get_suite() {
        CuSuite* suite = CuSuiteNew();
        SUITE_ADD_TEST(suite, test_create_alphas_and_radii_initial_a);
        SUITE_ADD_TEST(suite, test_create_alphas_and_radii_initial_r);
        SUITE_ADD_TEST(suite, test_create_alphas_and_radii_middle_a);
        SUITE_ADD_TEST(suite, test_create_alphas_and_radii_middle_r);
        SUITE_ADD_TEST(suite, test_create_alphas_and_radii_end_a);
        SUITE_ADD_TEST(suite, test_create_alphas_and_radii_end_r);

        SUITE_ADD_TEST(suite, test_attr_a);
        SUITE_ADD_TEST(suite, test_attr_r);

        SUITE_ADD_TEST(suite, test_attr_da);
        SUITE_ADD_TEST(suite, test_attr_dr);

        
        return suite;
    }

