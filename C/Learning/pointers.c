#include <stdio.h>

int main(){
	int ages[] = {24, 25, 27, 26};
	char *names[] = {"Swetha", "Darryl", "Hello", "Sam"};

	//set up
	int count = sizeof(ages)/sizeof(int);
	int i = 0;

	//Way 1
	for(i = 0; i < count; i++){
		printf("%s is %d years old\n", names[i], ages[i]);
	}

	//Way2
	int *current_age = ages;
	char **current_name = names;


}

