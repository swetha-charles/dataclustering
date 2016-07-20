#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>

#define pi M_PI

//prior parameters
struct prior_parameters{
	float variance_of_data;
	float ca;	//see Tino 2011 paper for explanation
	float cr;	//see Tino 2011 paper for explanation
	float w1;	//see Tino 2011 paper for explanation
	float w2;	//see Tino 2011 paper for explanation
};
struct prior_parameters *set_parameters(float variance_of_data, float ca, float cr, float w1, float w2);
void destroy_prior_parameters(struct prior_parameters *parameters);

//alphas_and_radii
struct alphas_and_radii{

	float *alpha_array_pointer;
	float *radius_array_pointer;
	int no_of_alphas;
	int no_of_radii;
	float da;
	float dr;


};
struct alphas_and_radii *create_alphas_and_radii(float delta_alpha, float delta_r);
void destroy_alphas_and_radii(struct alphas_and_radii *alphas_and_radii_to_destroy);


//calculating_priors
struct priors{
	float *p_alpha;
	float *p_r_given_alpha;
	float *total_prior;

};
struct priors;
void calculate_priors();
struct priors *create_prior_arrays(int no_of_alphas, int no_of_radii);
float calculate_p_alpha(float alpha, float ca);
float calculate_prior_r_given_alpha(float radius, float alpha, float cr, float w1, float w2);
void destroy_priors(struct priors *priors);

//process data
struct data{
	int no_data_points;
	float *data_x;
	float *data_y;
};

struct ht_results{
	float *p_r_alpha_given_x;
	float *p_r_alpha_given_data;
	float *p_alpha_given_data;
	
};
struct data *create_data_array();
struct ht_results *init_ht_results(int no_of_alphas, int no_of_radii, int no_data_points);
void get_posterior(float x1, float x2, int i, float variance_of_data, 
					struct priors *priors,
					struct ht_results *ht_results, 
					struct alphas_and_radii *alphas_and_radii, 
					struct data *data);
float get_p_x(float x1, float x2, float variance_of_data,struct alphas_and_radii *alphas_and_radii, struct priors *priors);
float p_x_given_alpha_r(float x1, float x2, float alpha, float radius, float variance_of_data);
void get_p_r_alpha_given_x(float x1, float x2, float variance_of_data, float p_x,
							 struct ht_results *ht_results, struct alphas_and_radii *alphas_and_radii, struct priors *priors, struct data *data);
void get_p_alpha_given_x(int index,  struct ht_results *ht_results, struct alphas_and_radii *alphas_and_radii);

//read_data.c
struct data *create_data_array(int size);
void destroy_data_array(struct data* data);

void store_x1_data(struct data *data, float x1);
float convert_char_to_int(char *text);

void store_x2_data(struct data *data, float x2);