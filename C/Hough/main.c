
#include "hough_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>


int main(){

	struct prior_parameters *prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	struct alphas_and_radii *alphas_and_radii = alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	struct priors *priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);


	//automatically stores the calculted priors within the struct called priors
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//read data and store into the struct called data
	struct data* data = retrieve_data(55681, 3,"DATA/x.dat", "DATA/y.dat");

	//code is currently taking the mean. Could also take median. 
	average_data(data);

	//run Hought Transform 
	struct ht_results* ht_results =  do_ht(data, prior_parameters, priors, alphas_and_radii);
	 
	// FILE* posterior_p_r_alpha_given_data = fopen("posterior_p_r_alpha_given_data.txt", "w");
	// FILE* posterior_p_alpha_given_data = fopen("posterior_p_alpha_given_data.txt", "w");


	//savePosteriorToFile(posterior_p_r_alpha_given_data, posterior_p_alpha_given_data, ht_results,alphas_and_radii, data);

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);
	
    
	return 0;
}