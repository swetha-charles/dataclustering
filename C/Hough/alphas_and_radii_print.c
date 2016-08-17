#include "hough_header.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void print_alpha_array(){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	int alphaNumber = alphas_and_radii->no_of_alphas;
	int i = 0;

	for(i = 0; i < alphaNumber; i++){
		printf("alpha: %i, %f\n",i , alphas_and_radii->alpha_array_pointer[i]);
	}
	printf("Total number of alphas: %i\n", alphaNumber);
	destroy_alphas_and_radii(alphas_and_radii);

}

void print_radius_array(){
	struct alphas_and_radii *alphas_and_radii = create_alphas_and_radii(0.05, 0.05);

	int radius_nmber = alphas_and_radii->no_of_radii;
	int i = 0;

	for(i = 0; i < radius_nmber; i++){
		printf("radius: %i, %f\n", i, alphas_and_radii->radius_array_pointer[i]);
	}
	printf("Total number of alphas: %i\n", radius_nmber);
	destroy_alphas_and_radii(alphas_and_radii);

}

int main(int argc, char const *argv[])
{
	print_alpha_array();
	print_radius_array();
	return 0;
}