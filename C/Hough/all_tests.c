#include "CuTest.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

CuSuite* prior_parameters_get_suite();
    
    void RunAllTests(void) {
        CuString *output = CuStringNew();
        CuSuite* suite = CuSuiteNew();
        
        CuSuiteAddSuite(suite, prior_parameters_get_suite());
    
        CuSuiteRun(suite);
        CuSuiteSummary(suite, output);
        CuSuiteDetails(suite, output);
        printf("%s\n", output->buffer);
    }
    
    int main(void) {
        RunAllTests();
    }