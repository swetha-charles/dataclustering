#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>

#define pi M_PI

//prior parameters
struct prior_parameters{
	double variance_of_data;
	double ca;	//see Tino 2011 paper for explanation
	double cr;	//see Tino 2011 paper for explanation
	double w1;	//see Tino 2011 paper for explanation
	double w2;	//see Tino 2011 paper for explanation
};
struct prior_parameters *set_parameters(double variance_of_data, double ca, double cr, double w1, double w2);
void destroy_prior_parameters(struct prior_parameters *parameters);

//alphas_and_radii
struct alphas_and_radii{

	double *alpha_array_pointer;
	double *radius_array_pointer;
	int no_of_alphas;
	int no_of_radii;
	double da;
	double dr;


};
struct alphas_and_radii *create_alphas_and_radii(double delta_alpha, double delta_r);
void destroy_alphas_and_radii(struct alphas_and_radii *alphas_and_radii_to_destroy);


//calculating_priors
struct priors{
	double *p_alpha;
	double *p_r_given_alpha;
	double *total_prior;

};
struct priors;
void calculate_priors();
struct priors *create_prior_arrays(int no_of_alphas, int no_of_radii);
double calculate_p_alpha(double alpha, double ca);
double calculate_prior_r_given_alpha(double radius, double alpha, double cr, double w1, double w2);
void destroy_priors(struct priors *priors);

//process data
struct data{
	int no_of_rows;
	int no_of_columns;
	
	double *data_x;
	double *data_y;
	double *data_x_mean;
	double *data_y_mean;
	
};

struct ht_results{
	int no_of_data_points;
	int no_of_alphas;
	int no_of_radii;

	double *p_r_alpha_given_x;
	double *p_r_alpha_given_data;
	double *p_alpha_given_data;


};
void delete_ht_results(struct ht_results *ht_results);
struct data *create_data_array();
struct ht_results *init_ht_results(int no_of_alphas, int no_of_radii, int no_data_points);
struct ht_results* do_ht(struct data *data, struct prior_parameters *prior_parameters, struct priors *priors, struct alphas_and_radii *alphas_and_radii);
void get_posterior(double x1, double x2, int i, double variance_of_data, 
					struct priors *priors,
					struct ht_results *ht_results, 
					struct alphas_and_radii *alphas_and_radii, 
					struct data *data);
double get_p_x(double x1, double x2, double variance_of_data,struct alphas_and_radii *alphas_and_radii, struct priors *priors);

double p_x_given_alpha_r(double x1, double x2, double alpha, double radius, double variance_of_data);

double p_x_given_alpha_r_debug(double x1, double x2, double alpha, double radius, double variance_of_data, FILE* file);
void get_p_r_alpha_given_x(double x1, double x2, double variance_of_data, double p_x,
							 struct ht_results *ht_results, struct alphas_and_radii *alphas_and_radii, struct priors *priors, struct data *data);
double calculate_p_r_alpha_given_x(double x1, double x2, double variance_of_data, double alpha, double r, double p_x, 
							struct alphas_and_radii* alphas_and_radii, struct priors *priors, int i , int j);
void get_p_alpha_given_x(int index,  struct ht_results *ht_results, struct alphas_and_radii *alphas_and_radii);

//read_data.c
struct data *create_data_array(int size, int columns);
void destroy_data_array(struct data* data);

struct data* retrieve_data(int no_of_data_points, int columns,  char* filename_x, char* filename_y);

double convert_char_to_int(char *text);

void store_x2_data(struct data *data, double x2, int row, int column);
void store_x1_data(struct data *data, double x1, int row, int column);
void average_data(struct data* data);
void savePosteriorToFile(FILE* p_r_alpha_given_data, FILE* p_alpha_given_data, struct ht_results* ht_results, struct alphas_and_radii* alphas_and_radii, struct data* data);
