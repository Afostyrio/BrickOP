#include "printer.h"

void printVector(double* vec, int size){
	int i;
	printf("\n");
	for(i=0; i<size; i++){
		printf("%lf ", vec[i]);
	}
	printf("\n");
	return;
}

void printCharVector(char* vec, int size){
	int i;
	printf("\n");
	for(i=0; i<size; i++){
		printf("%c ", vec[i]);
	}
	printf("\n");
	return;
}
