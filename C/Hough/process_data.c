#include "hough_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>



struct ht_results *init_ht_results(int no_of_alphas, int no_of_radii, int no_data_points){
	double *p_r_alpha_given_x = malloc(sizeof(double) * no_of_radii * no_of_alphas ); // store p(a, r | x)

	//this will store cumulative p(r, a | xi)
	//calloc so that the memory is initialized to 0
	double *p_r_alpha_given_data = calloc( no_of_radii * no_of_alphas, sizeof(double));


	//store p(a|Data); each row is for a single xi point. Each column, are the p(a|xi) values for a 
	//given alpha. This is a 2D array where the number of rows is the number of data points 
    // and the number of columns is the number of alphas. 
	double *p_alpha_given_data = malloc(sizeof(double) * no_data_points * no_of_alphas); 


	struct ht_results *ht_results = malloc(sizeof(struct ht_results)); //get storage for ht_results
	ht_results->p_r_alpha_given_x = p_r_alpha_given_x;
	ht_results->p_r_alpha_given_data = p_r_alpha_given_data;
	ht_results->p_alpha_given_data = p_alpha_given_data;

	return ht_results;
}

void delete_ht_results(struct ht_results *ht_results){
	free(ht_results->p_alpha_given_data);
	free(ht_results->p_r_alpha_given_data);
	free(ht_results->p_r_alpha_given_x);
	free(ht_results);
}


void do_ht(struct data *data, struct prior_parameters *prior_parameters, struct priors *priors, struct alphas_and_radii *alphas_and_radii){
	//create a struct to hold results of HT
	int no_alphas = alphas_and_radii->no_of_alphas;
	int no_radii = alphas_and_radii->no_of_radii;
	int no_data_points = data->no_data_points;

	struct ht_results *ht_results = init_ht_results(no_alphas, no_radii, no_data_points);

	int i = 0;
	for(; i < data->no_data_points; i++){
		double x1 = data->data_x[i];
		double x2 = data->data_y[i];

		get_posterior(x1, x2,i, prior_parameters->variance_of_data, priors, ht_results, alphas_and_radii, data);

	}
}

void get_posterior(double x1, double x2, int i, double variance_of_data, 
					struct priors *priors,
					struct ht_results *ht_results, 
					struct alphas_and_radii *alphas_and_radii, 
					struct data *data){

	double p_x = get_p_x(x1, x2, variance_of_data, alphas_and_radii, priors);
	//TESTED!

	//this function automatically stores the results in ht_results
	get_p_r_alpha_given_x(x1, x2, variance_of_data, p_x, ht_results, alphas_and_radii, priors, data);

	//this function automatically stores the results in ht_results
	get_p_alpha_given_x(i,ht_results, alphas_and_radii );

	//now that p(alpha | x ) has been added to p(alpha | data), we can clear p(alpha | x)
	//I've chosen to leave it be - it will get re written when p_r_alpha_given_x is called next. 
}

void get_p_alpha_given_x(int index,  struct ht_results *ht_results, struct alphas_and_radii *alphas_and_radii){
	int i =0;
	int j = 0;
	int sum_alpha = 0;
	double delta_r = alphas_and_radii->dr;

	for(i =0; i < alphas_and_radii->no_of_alphas; i++){
		
		for(j = 0; j < alphas_and_radii->no_of_radii; j++){
			sum_alpha += ht_results->p_r_alpha_given_x[(i * alphas_and_radii->no_of_alphas) + j];
		}
		ht_results->p_alpha_given_data[(index * alphas_and_radii->no_of_alphas) + i] = sum_alpha * delta_r; 
		sum_alpha = 0;
	}
}

void get_p_r_alpha_given_x(double x1, double x2, double variance_of_data, double p_x,
							 struct ht_results *ht_results, struct alphas_and_radii *alphas_and_radii, struct priors *priors, struct data *data){
	int i = 0;
	int j = 0;
	int no_of_alphas = alphas_and_radii->no_of_alphas;
	int no_of_radii = alphas_and_radii->no_of_radii;


		for(i = 0; i < alphas_and_radii->no_of_alphas; i++){
			double alpha = alphas_and_radii->alpha_array_pointer[i];

			for(j = 0 ; j < alphas_and_radii->no_of_radii; j++){

				double r = alphas_and_radii->radius_array_pointer[j];

				double result = calculate_p_r_alpha_given_x(x1, x2, variance_of_data,  alpha, r, p_x, alphas_and_radii, priors, i, j);
				//printf("alpha: %i,alpha_val %f, r: %i, r_val :%f, p_r_alpha_given_x: %e\n",i, alpha,j,r, result);
				
				ht_results->p_r_alpha_given_x[(j *no_of_alphas) + i] = (result); //unsure about data_point division
			
				ht_results->p_r_alpha_given_data[(j * no_of_radii) + i] += (result / data->no_data_points);

			}
	}
}

double calculate_p_r_alpha_given_x(double x1, double x2, double variance_of_data, double alpha, double r, double p_x, 
							struct alphas_and_radii* alphas_and_radii, struct priors *priors, int i , int j){

	double result = (p_x_given_alpha_r(x1, x2, alpha, r, variance_of_data) * priors->total_prior[(j * alphas_and_radii->no_of_alphas) + i])/p_x;
	return result;

}

double get_p_x(double x1, double x2, double variance_of_data,struct alphas_and_radii *alphas_and_radii, struct priors *priors){
	double result = 0;
	int i= 0;
	int j = 0;

	for(i = 0; i < alphas_and_radii->no_of_alphas; i++){
		double alpha = alphas_and_radii->alpha_array_pointer[i];

		for(j = 0; j < alphas_and_radii->no_of_radii; j++){
			double r = alphas_and_radii->radius_array_pointer[j];
//			prior is p(a, r)
			// printf("alpha: %i, r: %i\n", i, j);
			// printf("alpha: %f, r: %f\n", alpha, r);
			// printf("noise model: %e ", p_x_given_alpha_r(x1, x2, alpha, r, variance_of_data));
			// printf("priors: %e\n", priors->total_prior[(j * alphas_and_radii->no_of_alphas) + i]);
			result += p_x_given_alpha_r(x1, x2, alpha, r, variance_of_data) * priors->total_prior[(j * alphas_and_radii->no_of_alphas) + i];

		}
	}
	printf("%f\n", result);
	return (result * alphas_and_radii->da * alphas_and_radii->dr);

}
//OR otherwise called the noise model
double p_x_given_alpha_r(double x1, double x2, double alpha, double radius, double variance_of_data){
	//NB this code uses the GNU scientific library for helping with matrix operators. 
	//#include gsl_matrix.h at the top of the file includes the library.


	double mu_1 = radius*cos(alpha);
	double mu_2 = radius*sin(alpha);

	gsl_matrix *mu  = gsl_matrix_alloc(2,1);
	gsl_matrix_set (mu, 0, 0,mu_1);
	gsl_matrix_set (mu, 1, 0,mu_2);

	gsl_matrix *covar = gsl_matrix_alloc (2, 2);
	gsl_matrix_set (covar, 0, 0, 1);
	gsl_matrix_set (covar, 0, 1, 0.5);
	gsl_matrix_set (covar, 1, 0, 0.5);
	gsl_matrix_set (covar, 1, 1, 1);

	//this matrix will be copied with covar's inputs
	//later, it will be turned into the inverse covariance
	gsl_matrix *inverse_covariance = gsl_matrix_alloc (2, 2);
	gsl_matrix_memcpy(inverse_covariance, covar);

	gsl_matrix *x = gsl_matrix_alloc(2,1);
	gsl_matrix_set (x, 0, 0, x1);
	gsl_matrix_set (x, 1, 0, x2);

	gsl_matrix *x_copy = gsl_matrix_alloc(2,1);
	gsl_matrix_memcpy(x_copy, x);

	double scale_inv_covar = (2)/(3* variance_of_data*variance_of_data);
	gsl_matrix_scale(inverse_covariance, scale_inv_covar);

	// printf("00: %f\n", gsl_matrix_get(inverse_covariance, 0, 0));
	// printf("01: %f\n", gsl_matrix_get(inverse_covariance, 0, 1));
	// printf("10: %f\n", gsl_matrix_get(inverse_covariance, 1, 0));
	// printf("11: %f\n", gsl_matrix_get(inverse_covariance, 1, 1));


	gsl_matrix_sub(x_copy, mu); //(x - mu)
	gsl_matrix *x_minus_mu = x_copy;

	// printf("00: %f\n", gsl_matrix_get(x_minus_mu, 0, 0));
	// printf("10: %f\n", gsl_matrix_get(x_minus_mu, 1, 0));
	// printf("10: %f\n", gsl_matrix_get(inverse_covariance, 1, 0));
	// printf("11: %f\n", gsl_matrix_get(inverse_covariance, 1, 1));

	gsl_matrix *x_minus_mu_T = gsl_matrix_alloc(1,2);


	gsl_matrix_transpose_memcpy(x_minus_mu_T, x_minus_mu);//(x-mu)T
	// printf("00: %f\n", gsl_matrix_get(x_minus_mu_T, 0, 0));
	// printf("01: %f\n", gsl_matrix_get(x_minus_mu_T, 0, 1));


	//(x-mu)T * Inverse_covariance
	//result is stored in rsult_so_far
	gsl_matrix *result_so_far = gsl_matrix_alloc(1,2);

	int i =0;
	int j = 0;
	int k =0;
	double result = 0;

	//multiply (x-mu) T * inverse_covariance
	for(; i < 1; i++){
		for(; j<2; j++){
			for(k = 0; k < 2; k++){
				result += gsl_matrix_get(x_minus_mu_T, i, k) * gsl_matrix_get(inverse_covariance,k,j);
			}
			//printf("result : %f\n",result);
			gsl_matrix_set(result_so_far, i, j, result);
			result = 0;
		}
	}

	// printf("00: %f\n", gsl_matrix_get(result_so_far, 0, 0));
	// printf("01: %f\n", gsl_matrix_get(result_so_far, 0, 1));
	//TESTED SO FAR!


	//multiply result_so_far against x_minus_mu
	//gsl_matrix_mul_elements(result_so_far, x_minus_mu);
	i = 0;
	j = 0;
	k = 0;
	result = 0;

	for(;i<1;i++){
		for(;j<1;j++){
			for(k = 0; k <2; k++){
				result += gsl_matrix_get(result_so_far, i, k) * gsl_matrix_get(x_minus_mu, k, j);
			}
		
		}
	}



	gsl_matrix_free(result_so_far);
	gsl_matrix_free(x_minus_mu_T);
	gsl_matrix_free(x_copy);
	gsl_matrix_free(x);
	gsl_matrix_free(mu);
	gsl_matrix_free(inverse_covariance);
	gsl_matrix_free(covar);

	return (1 / (2*pi*variance_of_data*variance_of_data*sqrt(3)))*exp(-0.5* result);
}