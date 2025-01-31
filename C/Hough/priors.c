#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "hough_header.h"

#define pi M_PI

//creates arrays to hold the priors
struct priors *create_prior_arrays(int no_of_alphas, int no_of_radii){
	struct priors *priors = malloc(sizeof(struct priors));

	double *p_alpha = malloc(sizeof(double) * no_of_alphas);
	priors->p_alpha = p_alpha; //set up storage for p alpha

	double *p_r_given_alpha = malloc(sizeof(double) * no_of_radii * no_of_alphas);
	priors->p_r_given_alpha = p_r_given_alpha; //set up storate for p r given alpha

	double *total_prior = malloc(sizeof(double) * no_of_radii * no_of_alphas);
	priors->total_prior = total_prior; //set up storage for total priors (palpha * p r given alpha)

	return priors;
}

//deletes arrays holding the priors
void destroy_priors(struct priors *priors){
	free(priors->p_alpha);
	
	free(priors->p_r_given_alpha);
	
	free(priors->total_prior);
	
	free(priors);
	
}



void calculate_priors(struct alphas_and_radii *a_r, struct prior_parameters *parameters, struct priors *priors){
	int i, j, alphas;
	alphas = a_r->no_of_alphas;
	double *alpha_array = a_r->alpha_array_pointer;
	double *radii_array = a_r->radius_array_pointer;

	//outer loop iterates over the alphas
	for(i = 0; i < a_r->no_of_alphas; i++){
		double alpha = alpha_array[i]; //pull out current value of alpha

		//active prior
		double p_alpha = calculate_p_alpha(alpha, parameters->ca); //calculate p_alpha and store in a temporary variable

		//passive prior
		//double p_alpha = calculate_passive_p_alpha(alpha, parameters->ca);
		priors->p_alpha[i] = p_alpha; //store in prior storage array

		//inner loop iterates over the r's
		for(j = 0;j<a_r->no_of_radii; j++){
			double radius = *(radii_array + j);
			
			//change this value to wash out the priors

			//for active priors
			double p_r_given_alpha = calculate_prior_r_given_alpha(radius, alpha, parameters->cr, parameters->w1, parameters->w2); //calculaye p_r_given_alpha

			//for passive priors
			//double p_r_given_alpha = calculate_passive_prior_r_given_alpha(radius, alpha, parameters->cr, parameters->w1, parameters->w2); //calculaye p_r_given_alpha
			priors->p_r_given_alpha[(j*alphas)+i] = p_r_given_alpha; //store it in a 2D array 

			double total_prior = p_r_given_alpha * p_alpha; //calculate total prior
			priors->total_prior[(j*alphas) + i] = total_prior; //store this in 2D array. 
			//printf("%e, ", total_prior);
		}
		//printf("\n");
	}
}

double calculate_p_alpha(double alpha, double ca){
	double s = 2*(1-ca)/((pi*pi) * (1+ca));
	
	if ((alpha >= 0) && (alpha <= pi/4)){
		return (-s*alpha + 1/(2*pi));
	}
   
    else if ((alpha > pi/4) && (alpha <= 3*pi/4)){
   		return (s*alpha + (3*ca - 1)/(2*pi*(1 + ca)));
    }
    else if ((alpha > 3*pi/4) && (alpha <= 5*pi/4)){
      	return (-s*alpha + (5 - 3*ca)/(2*pi*(1 + ca)));
    }
    else if ((alpha > 5*pi/4) && (alpha< 7*pi/4)){
       	return (s*alpha + (7*ca - 5)/(2*pi*(1 + ca)));
    }   
    else if( (alpha >= 7*pi/4) && alpha <= 2*pi){
    	//workaround - see Tino 2011
    	double modified_alpha = 2*pi - alpha;
    	return (-s*modified_alpha + 1/(2*pi));
    }                       
    
    fprintf(stderr, "ERROR: alpha not between 0 and 2pi, check your alphas\n" );
    return 0;
}

/*
	Use this to wash out priors
*/

double calculate_passive_p_alpha(double alpha, double ca){
	double s = 2*(1-ca)/((pi*pi) * (1+ca));
	
	if ((alpha >= 0) && (alpha <= 2*pi)){
		return (s*alpha + (3*ca - 1)/(2*pi*(1 + ca)));
	}
   
    fprintf(stderr, "ERROR: alpha not between 0 and 2pi, check your alphas\n" );
    return 0;
}

double calculate_prior_r_given_alpha(double radius, double alpha, double cr, double w1, double w2){

	double p1 = 2*exp(- (radius * radius)/(2*w1*w1) ) / (sqrt(2*pi) * w1);
	double p2 = 2*exp(- (radius * radius)/(2*w2*w2) ) / (sqrt(2*pi) * w2);
	double kappa = 0;
	
	double s = 2*(1-cr)/pi;
	if ((alpha >= 0) && (alpha <= pi/4)){
		kappa = -s*alpha + (1 + cr)/2;
	}
  
   else if ((alpha > pi/4) && (alpha <= 3*pi/4)){
   		kappa = s*alpha + (3*cr - 1)/2;
   }
       
   else if ((alpha > 3*pi/4) && (alpha <= 5*pi/4)){
   	    kappa = -s*alpha + (-3*cr + 5)/2;
   }
   else if((alpha > 5*pi/4) && (alpha<= 7*pi/4)){
   	    kappa = s*alpha + (7*cr - 5)/2;
   }
   else if((alpha > 7*pi/4) && (alpha<= 2*pi)){
   		double modified_alpha = 2 * pi - alpha;
   		kappa = -s*modified_alpha + (1 + cr)/2;
   } else {
   		fprintf(stderr, "ERROR: alphas not between 0 and 2pi, check your alphas\n" );
   		return 0;
   }
                                    
	double prior_r = (1 - kappa)*p1 + kappa*p2;
	return prior_r;
   
  }

/*
	This is formula is used to wash out the priors. I.e. equal priors throughout 
*/
double calculate_passive_prior_r_given_alpha(double radius, double alpha, double cr, double w1, double w2){

	double p1 = 2*exp(- (radius * radius)/(2*w1*w1) ) / (sqrt(2*pi) * w1);
	double p2 = 2*exp(- (radius * radius)/(2*w2*w2) ) / (sqrt(2*pi) * w2);
	double kappa = 0;
	
	double s = 2*(1-cr)/pi;
	if ((alpha >= 0) && (alpha<= 2*pi)){
		kappa = s*alpha + (3*cr - 1)/2;

	}
  
  else {
   		fprintf(stderr, "ERROR: alphas not between 0 and 2pi, check your alphas\n" );
   		return 0;
   }
                                    
	double prior_r = (1 - kappa)*p1 + kappa*p2;
	return prior_r;
   
}