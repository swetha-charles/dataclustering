#include <stdio.h>
#include <math.h>

# define pi M_PI;	//pi now refers to the value of M_PI

int main(){
	int c; //this is used to read a chacracter

	while((c = getchar())!= EOF){ //this is quicker way of doing what we want to do
		putchar(c);
		
	}
	printf("AOK\n");
	return 0;
}

