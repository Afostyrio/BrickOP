#include "pemdas.h"

FILE* getLineFromFile(char filename[MAX_FILENAME_SIZE]){
	FILE* ptr = fopen(filename, "r");
	if(!ptr){
		printf("Error de archivo.");
		return NULL;
	}
	char* str = malloc(MAX_OPERATION_SIZE * sizeof(char));
	fgets(str, MAX_OPERATION_SIZE, ptr);
	fclose(ptr);
	ptr = fopen("lineFile.txt", "w");
	fputs(str, ptr);
	free(str);
	fclose(ptr);
	ptr = fopen("lineFile.txt", "r");
	return ptr;
}

double pemdasSolve(FILE* stream){
	int numNumbers = countNumbers(stream);
	double* numbers = malloc(numNumbers * sizeof(double)), final;
	char* operators = malloc(numNumbers * sizeof(char));
	int i;
	for(i=0; i<numNumbers; i++){
		fscanf(stream, "%lf %c", &numbers[i], &operators[i]);
	}
	printVector(numbers, numNumbers);
	printCharVector(operators, numNumbers);
	for(i=0; i<numNumbers; i++){
		if(operators[i] == '-'){
			numbers[i+1] *= -1;
			operators[i] = '+';
		}
		if(operators[i] == '/'){
			numbers[i+1] = 1/numbers[i+1];
			operators[i] = '*';
		}		
		if(operators[i] == '^'){
			numbers[i+1] = pow(numbers[i], numbers[i+1]);
			operators[i] = '*';
			numbers[i] = 1;
		}
	}
	printVector(numbers, numNumbers);
	printCharVector(operators, numNumbers);
	
	for(i=0; i<numNumbers; i++){
		if(operators[i] == '*'){
			numbers[i+1] *= numbers[i];
			operators[i] = '+';
			numbers[i] = 0;
		}
	}

	printVector(numbers, numNumbers);
	printCharVector(operators, numNumbers);

	free(operators);
	final = sumaVector(numbers, numNumbers);
	free(numbers);
	
	return final;
}


int countNumbers(FILE* stream){
	int counter = 0;
	double aux;
	char auxChar;
	while(!feof(stream)){
		counter++;
		fscanf(stream, "%lf %c ", &aux);
	}
	rewind(stream);
	return counter;
}

int countOperators(FILE* stream){
	int counter = 0;
	double aux;
	char auxChar;
		while(!feof(stream)){
		counter++;
		fscanf(stream, "%lf %c ", &aux, &auxChar);
		printf("%c ", auxChar);
	}
	rewind(stream);	
	return counter;
}

double sumaVector(double* vec, int size){
	int i;
	double sum = 0;
	for(i=0; i<size; i++){
		sum += vec[i];
	}
	return sum;
}
