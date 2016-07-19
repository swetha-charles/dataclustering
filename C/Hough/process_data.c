#include "hough_header.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>



struct ht_results *init_ht_results(int no_of_alphas, int no_of_radii, int no_data_points){
	float *p_r_alpha_given_x = malloc(sizeof(float) * no_of_radii * no_of_alphas ); // store p(a, r | x)

	float *p_r_alpha_given_data = malloc(sizeof(float) * no_of_radii * no_of_alphas);
	memset(p_r_alpha_given_data, 0, sizeof(float) * no_of_radii * no_of_alphas); //TEST

	//store p(a|Data); each row is for a single xi point. Each column, are the p(a|xi) values for a 
	//given alpha. This is a 2D array where the number of rows is the number of data points 
    // and the number of columns is the number of alphas. 
	float *p_alpha_given_data = malloc(sizeof(float) * no_data_points * no_of_alphas); 


	struct ht_results *ht_results = malloc(sizeof(struct ht_results)); //get storage for ht_results
	ht_results->p_r_alpha_given_x = p_r_alpha_given_x;
	ht_results->p_r_alpha_given_data = p_r_alpha_given_data;
	ht_results->p_alpha_given_data = p_alpha_given_data;

	return ht_results;
}

void delete_ht_results(struct ht_results *ht_results){
	//TODO
}


void do_ht(struct data *data, struct prior_parameters *prior_parameters, struct priors *priors, struct alphas_and_radii *alphas_and_radii){
	//create a struct to hold results of HT
	int no_alphas = alphas_and_radii->no_of_alphas;
	int no_radii = alphas_and_radii->no_of_radii;
	int no_data_points = data->no_data_points;

	struct ht_results *ht_results = init_ht_results(no_alphas, no_radii, no_data_points);

	int i = 0;
	for(; i < data->no_data_points; i++){
		float x1 = data->data_x[i];
		float x2 = data->data_y[i];

		get_posterior(x1, x2,i, prior_parameters->variance_of_data, priors, ht_results, alphas_and_radii, data);

	}
}

void get_posterior(float x1, float x2, int i, float variance_of_data, 
					struct priors *priors,
					struct ht_results *ht_results, 
					struct alphas_and_radii *alphas_and_radii, 
					struct data *data){

	float p_x = get_p_x(x1, x2, variance_of_data, alphas_and_radii, priors);

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
	float delta_r = alphas_and_radii->dr;

	for(; i < alphas_and_radii->no_of_alphas; i++){
		
		for(; j < alphas_and_radii->no_of_radii; j++){
			sum_alpha += ht_results->p_r_alpha_given_x[(i * alphas_and_radii->no_of_alphas) + j];
		}
		ht_results->p_alpha_given_data[(index * alphas_and_radii->no_of_alphas) + i] = sum_alpha * delta_r; 
		sum_alpha = 0;
	}
}

void get_p_r_alpha_given_x(float x1, float x2, float variance_of_data, float p_x,
							 struct ht_results *ht_results, struct alphas_and_radii *alphas_and_radii, struct priors *priors, struct data *data){
	int i = 0;
	int j = 0;
		for(; i < alphas_and_radii->no_of_alphas; i++){
			float alpha = alphas_and_radii->alpha_array_pointer[i];
			for(j = 0 ; j < alphas_and_radii->no_of_radii; j++){
				float r = alphas_and_radii->radius_array_pointer[j];
				float result = (p_x_given_alpha_r(x1, x2, alpha, r, variance_of_data) * priors->total_prior[(i * alphas_and_radii->no_of_alphas) + j])/p_x;
				ht_results->p_r_alpha_given_x[(i * alphas_and_radii->no_of_alphas) + j] = (result/data->no_data_points); //unsure about data_point division
				ht_results->p_r_alpha_given_data[(i * alphas_and_radii->no_of_alphas) + j] += (result / data->no_data_points);

			}
	}
}

float get_p_x(float x1, float x2, float variance_of_data,struct alphas_and_radii *alphas_and_radii, struct priors *priors){
	float result = 0;
	int i= 0;
	int j = 0;

	for(; i < alphas_and_radii->no_of_alphas; i++){
		float alpha = alphas_and_radii->alpha_array_pointer[i];

		for(; j < alphas_and_radii->no_of_radii; j++){
			float r = alphas_and_radii->radius_array_pointer[j];
			//prior is p(a, r)
			result += p_x_given_alpha_r(x1, x2, alpha, r, variance_of_data) * priors->total_prior[(i * alphas_and_radii->no_of_alphas) + j];

		}
	}

	return (result * alphas_and_radii->da * alphas_and_radii->dr);

}
//OR otherwise called the noise model
float p_x_given_alpha_r(float x1, float x2, float alpha, float radius, float variance_of_data){
	//NB this code uses the GNU scientific library for helping with matrix operators. 
	//#include gsl_matrix.h at the top of the file includes the library.


	float mu_1 = radius*cos(alpha);
	float mu_2 = radius*sin(alpha);

	gsl_matrix *covar = gsl_matrix_alloc (2, 2);
	gsl_matrix_set (covar, 0, 0, 1);
	gsl_matrix_set (covar, 0, 1, 0.5);
	gsl_matrix_set (covar, 1, 0, 0.5);
	gsl_matrix_set (covar, 1, 1, 0.5);

	//this matrix will be coped with covar's inputs
	//later, it will be turned into the inverse covariance
	gsl_matrix *inverse_covariance = gsl_matrix_alloc (2, 2);
	gsl_matrix_memcpy(inverse_covariance, covar);

	gsl_matrix *mu  = gsl_matrix_alloc(2,1);
	gsl_matrix_set (mu, 0, 0,mu_1);
	gsl_matrix_set (mu, 1, 0,mu_2);

	gsl_matrix *x = gsl_matrix_alloc(2,1);
	gsl_matrix_set (x, 0, 0, x1);
	gsl_matrix_set (x, 1, 0, x2);

	gsl_matrix *x_copy = gsl_matrix_alloc(2,1);
	gsl_matrix_memcpy(x_copy, x);

	double scale_inv_covar = (2)/(3* variance_of_data*variance_of_data);
	gsl_matrix_scale(inverse_covariance, scale_inv_covar);

	gsl_matrix_sub(x_copy, mu); //(x - mu)
	gsl_matrix *x_minus_mu = x_copy;

	gsl_matrix *x_minus_mu_T = gsl_matrix_alloc(1,2);

	gsl_matrix_transpose_memcpy(x_minus_mu_T, x_minus_mu);//(x-mu)T

	//(x-mu)T * Inverse_covariance
	//result is stored in rsult_so_far
	gsl_matrix *result_so_far = gsl_matrix_alloc(1,2);

	int i =0;
	int j = 0;
	int k =0;
	float result = 0;
	//multiply (x-mu) T * inverse_covariance
	for(; i < 1; i++){
		for(; j<2; j++){
			for(; k < 2; k++){
				result += gsl_matrix_get(x_minus_mu_T, i, k) * gsl_matrix_get(inverse_covariance,k,j);
			}
			gsl_matrix_set(result_so_far, i, j, result);
			result = 0;
		}
	}

	//multiply result_so_far against x_minus_mu
	//gsl_matrix_mul_elements(result_so_far, x_minus_mu);
	i = 0;
	j = 0;
	k = 0;
	result = 0;

	for(;i<1;i++){
		for(;j<1;j++){
			for(; k <2; k++){
				result += gsl_matrix_get(result_so_far, i, k) * gsl_matrix_get(x_minus_mu, k, j);
			}
		
		}
	}

	//NEED TO DE ALLOCATE MEMORY!
	return (1 / (2*pi*variance_of_data*variance_of_data*sqrt(3)))*exp(result);
}