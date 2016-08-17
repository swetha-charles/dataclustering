#include "acca_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>

/*
 Use this file to run the unit tests for the program. 
 Each set of unit tests is places in a suite.

 The entire set of suites is then run here. 
*/
int main(int argc, char const *argv[])
{
	suite_tests_cluster();
	return 0;
}