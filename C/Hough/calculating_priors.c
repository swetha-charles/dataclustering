#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "hough_header.h"

#define pi M_PI

//creates arrays to hold the priors
struct priors *create_prior_arrays(int no_of_alphas, int no_of_radii){
	struct priors *priors = malloc(sizeof(priors));

	float *p_alpha = malloc(sizeof(float) * no_of_alphas);
	priors->p_alpha = p_alpha; //set up storage for p alpha

	float *p_r_given_alpha = malloc(sizeof(float) * no_of_radii * no_of_alphas);
	priors->p_r_given_alpha = p_r_given_alpha; //set up storate for p r given alpha

	float *total_prior = malloc(sizeof(float) * no_of_radii * no_of_alphas);
	priors->total_prior = total_prior; //set up storage for total priors (palpha * p r given alpha)

	return priors;
}

//deletes arrays holding the priors
void delete_priors(struct priors *priors){
	free(priors->p_alpha);
	free(priors->p_r_given_alpha);
	free(priors->total_prior);
	free(priors);
}



void calculate_priors(struct alphas_and_radii *a_r, struct prior_parameters *parameters, struct priors *priors){
	int i, j, alphas;
	alphas = a_r->no_of_alphas;
	float *alpha_array = a_r->alpha_array_pointer;
	float *radii_array = a_r->radius_array_pointer;

	//outer loop iterates over the alphas
	for(i = 0; i < a_r->no_of_alphas; i++){
		float alpha = *(alpha_array+i); //pull out current value of alpha
		float p_alpha = calculate_p_alpha(alpha, parameters->ca); //calculate p_alpha and store in a temporary variable
		priors->p_alpha[i] = p_alpha; //store in prior storage array

		//inner loop iterates over the r's
		for(j = 0;j<a_r->no_of_radii; j++){
			float radius = *(radii_array + j);
			float p_r_given_alpha = calculate_prior_r_given_alpha(radius, alpha, parameters->cr, parameters->w1, parameters->w2); //calculaye p_r_given_alpha
			priors->p_r_given_alpha[(i*alphas)+j] = p_r_given_alpha; //store it in a "2D" array //WRITE TEST

			float total_prior = p_r_given_alpha * p_alpha; //calculate total prior
			priors->total_prior[(i*alphas) + j] = total_prior; //store this in 2D array. //WRITE TEST
		}
	}
}

float calculate_p_alpha(float alpha, float ca){
	float s = 2*(1-ca)/((pi*pi) * (1+ca));
	float result;
	
	if ((alpha >= -pi/4) && (alpha <= pi/4)){
		result = -s*alpha + 1/(2*pi);
	}
   
    else if (alpha <= 3*pi/4){
   		result = s*alpha + (3*ca - 1)/(2*pi*(1 + ca));
    }
    else if (alpha <= 5*pi/4){
      	 result = -s*alpha + (5 - 3*ca)/(2*pi*(1 + ca));
    }
    else{
       	 result = s*alpha + (7*ca - 5)/(2*pi*(1 + ca));
    }                              
       return result;
}

float calculate_prior_r_given_alpha(float radius, float alpha, float cr, float w1, float w2){

	float p1 = 2*exp(- (radius * radius)/(2*w1*w1) ) / (sqrt(2*pi) * w1);
	float p2 = 2*exp(- (radius * radius)/(2*w2*w2) ) / (sqrt(2*pi) * w2);
	float kappa;
	
	float s = 2*(1-cr)/pi;
	if ((alpha >= -pi/4) && (alpha <= pi/4)){
		 kappa = -s*alpha + (1 + cr)/2;
	}
  
   else if (alpha <= 3*pi/4){
   		 kappa = s*alpha + (3*cr - 1)/2;
   }
       
   else if (alpha <= 5*pi/4){
   	     kappa = -s*alpha + (-3*cr + 5)/2;
   }
     else{
     	kappa = s*alpha + (7*cr - 5)/2;
     }
                                
	float prior_r = (1 - kappa)*p1 + kappa*p2;
	return prior_r;
}

void calculate_and_store_priors(){
	
}