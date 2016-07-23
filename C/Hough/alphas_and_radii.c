#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //Gives C's library value of Pi
#include "hough_header.h"


#define pi M_PI

/*
* This file sets up the alpha array and the radii array
*/


/*
* Constructor. User provides delta_alpha and delta_r. These are used to set up 
* the alpha and radius arrays in the parameter space. 
*
*/
struct alphas_and_radii *create_alphas_and_radii(double delta_alpha, double delta_r){

	//calculate number of angles we will analyze
	int no_of_alphas = ((2*M_PI)/delta_alpha) + 1; //is the plus one needed? 
	//calculate number of radius' we will analyze
	int no_of_radii = ((3)/delta_r) + 1;

	//get memory for alpha array
	double *alpha_array = malloc(sizeof(double) * no_of_alphas);  
	assert(alpha_array != NULL); //if assert fails, program will abort
	memset(alpha_array, 0, sizeof(double) * no_of_alphas); //fill it with zeroes

	//get memory for radius array
	double *radius_array = malloc(sizeof(double) * no_of_radii);  
	assert(radius_array != NULL);

	
	int i =0;//weird workaround for C's compiler :/
	//fill the alpha arrays with incrementing angles from 
	// - pi/4 -->> 7pi/4, increment steps of delta_alpha
	for(; i < no_of_alphas-1 && alpha_array[i] < (7*pi)/4; i++){
		alpha_array[i] = (-pi/4) + i*delta_alpha;
	}
	alpha_array[no_of_alphas-1] = (7*pi)/4;

	i = 0; //reset counter
	//fill the radius array with incrementing no_of_radii from 
	// 0 -->> 3, increment steps of delta r
		for(; i < no_of_radii-1 && radius_array[i] < 3; i++){
		radius_array[i] = 0 + i *delta_r;
	}
	radius_array[no_of_radii-1] = 3;

	//get memory for parameter space
	struct alphas_and_radii *current_alphas_and_radii = malloc(sizeof(struct alphas_and_radii));
	
	//set the parameter space struct to be equal to the two blocks 
	//of array memory
	current_alphas_and_radii->alpha_array_pointer = alpha_array;
	current_alphas_and_radii->radius_array_pointer = radius_array;
	current_alphas_and_radii->no_of_alphas = no_of_alphas;
	current_alphas_and_radii->no_of_radii = no_of_radii;
	current_alphas_and_radii->da = delta_alpha;
	current_alphas_and_radii->dr = delta_r;

	return current_alphas_and_radii;

}

void destroy_alphas_and_radii(struct alphas_and_radii *alphas_and_radii_to_destroy){
	assert (alphas_and_radii_to_destroy != NULL);
	free (alphas_and_radii_to_destroy->alpha_array_pointer);
	free (alphas_and_radii_to_destroy->radius_array_pointer);
	free (alphas_and_radii_to_destroy);

}

