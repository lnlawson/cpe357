/*Name: Logan Lawson
 *Lab 1 : Part 2*/

#include "part4.h"

void lower(char arr[], char buff[]){
	int i;

	for(i = 0; *(arr + i) != '\0'; i++){
		*(buff + i) = tolower(*(arr + i));
	}
	*(buff + i) = '\0';
	return;
}

void lower_mutate(char arr[]){
	int i;

	for(i = 0; *(arr + i) != '\0'; i++){
		*(arr + i) = tolower(*(arr + i));
	}
	return;
}
