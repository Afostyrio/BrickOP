#include "pemdas.h"

void clearParen(char filename[MAX_FILENAME_SIZE]){
	FILE* stream = fopen(filename, "rb");
	char* str = malloc(MAX_OPERATION_SIZE * sizeof(char));
	fgets(str, MAX_OPERATION_SIZE, stream);
	fclose(stream);
	int i = 0, parenFirstPos = -1;
	while(str[i]){	
		if(str[i] == '('){
			parenFirstPos = i;
		}
		i++;
	}
	
	if(parenFirstPos < 0){
		return;
	}
	
	int parenLastPos = -1;
	i = parenFirstPos + 2;
	while(str[i] != ')'){
		i++;
	}
	parenLastPos = i;
	
	char* substr = malloc((parenLastPos-parenFirstPos)*sizeof(char));
	for(i=0; i<parenLastPos-parenFirstPos-1; i++){
		substr[i] = str[i+parenFirstPos+1];
	}
	substr[parenLastPos-parenFirstPos-1] = 0;
	FILE* subOperation = fopen("subOp.bin", "wb");
	fputs(substr, subOperation);
	fclose(subOperation);
	double result = pemdasSolve("subOp.bin");
	remove("subOp.bin");
	free(substr);
	
	stream = fopen(filename, "wb");
	if(!stream){
		printf("Error");
	}
	
	substr = malloc(MAX_OPERATION_SIZE * sizeof(char));
	for(i=0; i<parenFirstPos; i++){
		substr[i] = str[i];
	}
	substr[i] = 0;
	fputs(substr, stream);
	fprintf(stream, "%lf", result);
	i = 0;
	while(1){
		substr[i] = str[i+parenLastPos+1];
		if(substr[i] == 0){
			break;
		}
		fputc(substr[i], stream);
		i++;
	}
	fclose(stream);
	free(str); free(substr);
	
	clearParen(filename);
}

void solveLineByLine(char filename[MAX_FILENAME_SIZE]){
	FILE* whole = fopen(filename, "r");
	if(!whole){
		printf("Error de archivo.");
	}
	FILE* results = fopen("results.txt", "w");
	if(!results){
		printf("Error");
	}

	while(!feof(whole)){
		char* str = malloc(MAX_OPERATION_SIZE * sizeof(char));
		fgets(str, MAX_OPERATION_SIZE, whole);
		FILE* oneLine = fopen("auxfile.bin", "wb");
		fputs(str, oneLine);
		fclose(oneLine);
		fputs(str, results);
		free(str);
		clearParen("auxfile.bin");
		double ans = pemdasSolve("auxfile.bin");
		printf("%lf\n", ans);
		fseek(results, -2, SEEK_END);
		fprintf(results, " = %lf\n", ans);
		remove("auxfile.bin");
	}
	fclose(results);
	fclose(whole);
}

/*
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
*/

double pemdasSolve(char filename[MAX_FILENAME_SIZE]){
	FILE* stream = fopen(filename, "rb");
	int numNumbers = countNumbers(stream);
	double* numbers = malloc(numNumbers * sizeof(double)), final;
	char* operators = malloc(numNumbers * sizeof(char));
	int i;
	for(i=0; i<numNumbers; i++){
		fscanf(stream, "%lf %c", &numbers[i], &operators[i]);
	}
	fclose(stream);
//	printVector(numbers, numNumbers);
//	printCharVector(operators, numNumbers);

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
//	printVector(numbers, numNumbers);
//	printCharVector(operators, numNumbers);
	
	for(i=0; i<numNumbers; i++){
		if(operators[i] == '*'){
			numbers[i+1] *= numbers[i];
			operators[i] = '+';
			numbers[i] = 0;
		}
	}

//	printVector(numbers, numNumbers);
//	printCharVector(operators, numNumbers);

	free(operators);
	final = sumaVector(numbers, numNumbers);
	free(numbers);

	return final;
}

int countNumbers(FILE* stream){
	int counter = 0;
	double aux;
	while(!feof(stream)){
		counter++;
		fscanf(stream, "%lf %c ", &aux);
	}
	rewind(stream);
	return counter;
}

/*
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
*/

double sumaVector(double* vec, int size){
	if(!size){
		return 0;
	}
	return *vec + sumaVector(vec+1, size-1);
}

//void removeNewline(char* str){
//	int i = 0;
//	while(str[i] != '\n'){
//		i++;
//	}
//	str[i] = '\0';
//}

 
