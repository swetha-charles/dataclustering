#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"

void test_storage_p_r_alpha_given_x_cumulative_1(){
	struct priors *priors;

	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);

	struct ht_results* ht_results = init_ht_results(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii, 100);
	struct data* data = create_data_array(100, 3);

	calculate_priors(alphas_and_radii, prior_parameters, priors);

	//   alpha: -7.853982e-01, al_i 1, r: 2.000000e-01, r_i: 5, p: 2.641841e-182
	// x1: 1.106309e-01, x2: 5.183355e-02, sigma: 5.000000e-03
	get_posterior(1.106309e-01, 5.183355e-02, 0, 0.005, priors,ht_results, alphas_and_radii, data);

	int i  = 0;
	int j = 0;

	for( i = 0; i < alphas_and_radii->no_of_radii; i++){
		for(j = 0; j < alphas_and_radii->no_of_alphas; j++){
			
		}
	}

	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);
	destroy_data_array(data);
	delete_ht_results(ht_results);

	
}

int main(int argc, char const *argv[])
{

	test_storage_p_r_alpha_given_x_cumulative_1();
	/* code */
	return 0;
}