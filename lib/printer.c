#include "printer.h"

void printVector(double* vec, int size){
	int i;
	for(i=0; i<size; i++){
		printf("%lf ", vec[i]);
	}
	printf("\n");
	return;
}

void printCharVector(char* vec, int size){
	int i;
	for(i=0; i<size; i++){
		printf("%c ", vec[i]);
	}
	printf("\n");
	return;
}

void printString(char* vec){
	int i = 0;
	while(vec[i]){
		printf("%c", vec[i]);
		i++;
	}
}
