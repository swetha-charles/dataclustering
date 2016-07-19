#include <stdio.h>

#define MAXLINE 100

int max; //external variable
char line[MAXLINE];

enum boolean { //can use enum 
	TRUE, FALSE
};

int main(){

	extern int max; /*must declare the external variable again inside the method. Not needed here since source file
					  is where the external variable is defined anyway. In bigger files, it's common practice to include 
					  the external variable in a header file .h and so it's include in every other .c file via #include <> 
					  , this means that the extern is not needed. */

	char *string = "hello";

	
	return 0;

}

