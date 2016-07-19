#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
	
};

struct Person *Person_create(char *name, int age, int height, int weight){
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);
	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;

}

void Person_destroy(struct Person *who){
	assert(who != NULL);
	free(who->name);
	free(who);

}

void Person_print(struct Person *person){
	printf("Name: %s\n", person->name);
}

int main(){
	struct Person *swetha = Person_create("swetha", 25, 150, 60);

	Person_print(swetha);
	Person_destroy(swetha);

	return 0;
}

