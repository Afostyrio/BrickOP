#include "printer.h"

void printCompleteLineToFile(double* numbers, char* operators, int size, FILE* destination){
	int i;
	for(i=0; i<size-1; i++){
		fprintf(destination, "%lf %c ", numbers[i], operators[i]);
	}
	fprintf(destination, "%lf\n", numbers[i]);
}

void printStepToFile(double* numbers, char* operators, int size, FILE* destination){
	int i;
	for(i=0; i<size-1; i++){
		if((numbers[i] == 1 && operators[i] == '*') || (numbers[i] == 0 && operators[i] == '+')){
			continue;
		}
		fprintf(destination, "%lf %c ", numbers[i], operators[i]);
	}
	fprintf(destination, "%lf\n", numbers[i]);
}

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
