#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hough_header.h"

void print_p_alpha(){
	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	int no_of_alphas = alphas_and_radii->no_of_alphas;
	int index = 0;

	FILE* p_alpha = fopen("p_alpha.txt", "w");

	for(index = 0; index < no_of_alphas; index++){
		if(index  % 12 == 0){
			fprintf(p_alpha, "\n");
		}
		double p_a = priors->p_alpha[index];
		//fprintf(p_alpha, "alpha: %i, %e ", index,p_a);
		fprintf(p_alpha, " %e ", p_a);

			}

	fclose(p_alpha);
	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

}

void print_p_r_given_alpha(){
	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.005, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	int no_of_alphas = alphas_and_radii->no_of_alphas;
	int no_of_radii = alphas_and_radii->no_of_radii;

	FILE* p_r_given_alpha = fopen("p_r_given_alpha.txt", "w");

	int i = 0;
	int j = 0;
	for(i = 0; i < no_of_radii; i ++){
		for(j = 0; j < no_of_alphas; j ++){
			fprintf(p_r_given_alpha, "%f ", priors->p_r_given_alpha[(i * no_of_alphas) + j]);
			
		}
		fprintf(p_r_given_alpha, "\n\n");
	}

		

	fclose(p_r_given_alpha);
	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

}

void print_total(){
	struct priors *priors;
	struct prior_parameters *prior_parameters;
	struct alphas_and_radii *alphas_and_radii;

	prior_parameters = set_parameters(0.05, 0.9, 0.9, 1.9,2.0);
	alphas_and_radii = create_alphas_and_radii(0.05, 0.05);
	priors = create_prior_arrays(alphas_and_radii->no_of_alphas, alphas_and_radii->no_of_radii);
	calculate_priors(alphas_and_radii, prior_parameters, priors);

	int no_of_alphas = alphas_and_radii->no_of_alphas;
	int no_of_radii = alphas_and_radii->no_of_radii;

	FILE* p_r_given_alpha = fopen("c_prior_r_alpha.txt", "w");

	int i = 0;
	int j = 0;
	for(i = 0; i < no_of_radii; i ++){
		for(j = 0; j < no_of_alphas; j ++){
			fprintf(p_r_given_alpha, "%f ", priors->total_prior[(i * no_of_alphas) + j]);
			
		}
		fprintf(p_r_given_alpha, "\n\n");
	}

		

	fclose(p_r_given_alpha);
	destroy_prior_parameters(prior_parameters);
	destroy_alphas_and_radii(alphas_and_radii);
	destroy_priors(priors);

}


int main(int argc, char const *argv[])
{
	//print_p_alpha();
	return 0;
}