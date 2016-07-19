#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "hough_header.h"

/*
* This file sets up the initial parameters for caclulating the priors
*/



struct prior_parameters *set_parameters(float variance_of_data, float ca, float cr, float w1, float w2){
	//allocate memory
	struct prior_parameters *parameters = malloc(sizeof(struct prior_parameters));

	parameters->variance_of_data = variance_of_data;
	parameters->ca = ca;
	parameters->cr = cr;
	parameters->w1 = w1;
	parameters->w2 = w2;

	return parameters;
}

//destroy memory allocated to parameters 
void destroy_prior_parameters(struct prior_parameters *parameters){
	assert(parameters != NULL);
	free(parameters);

}
