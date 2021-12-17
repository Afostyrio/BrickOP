#include "pemdas.h"

void clearParen(char filename[MAX_FILENAME_SIZE], FILE* destination){
	FILE* stream = fopen(filename, "rb+");
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
		free(str);
		fclose(stream);
		return;
	}
	
	int parenLastPos = -1;
	i = parenFirstPos + 2;
	while(str[i] != ')'){
		i++;
	}
	parenLastPos = i;
	
	char* substr = malloc((parenLastPos-parenFirstPos+1)*sizeof(char));
	for(i=0; i<parenLastPos-parenFirstPos-1; i++){
		substr[i] = str[i+parenFirstPos+1];
	}
	substr[parenLastPos-parenFirstPos-1] = '\n';
	substr[parenLastPos-parenFirstPos] = 0;
	FILE* subOperation = fopen("subOp.bin", "wb+");
	fputs(substr, subOperation);
	free(substr);
	fclose(subOperation);
	subOperation = fopen("subOp.bin", "rb+");
	double result = pemdasSolve(subOperation, subOperation);
	rewind(subOperation);
	
	char* head = malloc(MAX_OPERATION_SIZE * sizeof(char));
	char* subStep = malloc(MAX_OPERATION_SIZE * sizeof(char));
	char* tail = malloc(MAX_OPERATION_SIZE * sizeof(char));

	for(i=0; i<parenFirstPos; i++){
		head[i] = str[i];
	}
	head[i] = 0;
	
	i = 0;
	while(1){
		tail[i] = str[i+parenLastPos+1];
		if(tail[i] == 0){
			break;
		}
		i++;
	}
	fgets(subStep, MAX_OPERATION_SIZE, subOperation);
	while(fgets(subStep, MAX_OPERATION_SIZE, subOperation) != NULL){
		fputs(head, destination);
		fprintf(destination, "(");

		fputs(subStep, destination);
		fseek(destination, -2, SEEK_END);
		fprintf(destination, ")");
		
		fputs(tail, destination);
	}
	fclose(subOperation);
	remove("subOp.bin");
	
	fputs(head, destination);
	fprintf(destination, "%lf", result);
	fputs(tail, destination);

	stream = fopen(filename, "wb");
	fputs(head, stream);
	fprintf(stream, "%lf", result);
	fputs(tail, stream);
	fclose(stream);
	free(str); free(subStep);
	free(head); free(tail);
	
	clearParen(filename, destination);
}

void solveLineByLine(char filename[MAX_FILENAME_SIZE]){
	FILE* whole = fopen(filename, "r");
	if(!whole){
		printf("Error de archivo."); return;
	}
	FILE* results = fopen("resultados.txt", "w");
	if(!results){
		printf("Error en creacion de archivo de resultados"); return;
	}

	while(!feof(whole)){
		char* str = malloc(MAX_OPERATION_SIZE * sizeof(char));
		fgets(str, MAX_OPERATION_SIZE, whole);
		FILE* oneLine = fopen("oneline.bin", "wb");
		fputs(str, oneLine);
		fclose(oneLine);
		fputs(str, results);
		free(str);
		clearParen("oneline.bin", results);
		oneLine = fopen("oneline.bin", "rb+");
		pemdasSolve(oneLine, results);
		fclose(oneLine);
		fprintf(results, "\n");
		remove("oneline.bin");
	}
	fclose(results);
	fclose(whole);
}

double pemdasSolve(FILE* stream, FILE* destination){
	int numNumbers = countNumbers(stream);
	double* numbers = malloc(numNumbers * sizeof(double)), final;
	char* operators = malloc(numNumbers * sizeof(char)), done = 0;
	int i;
	for(i=0; i<numNumbers; i++){
		fscanf(stream, "%lf %c", &numbers[i], &operators[i]);
	}

	for(i=0; i<numNumbers; i++){
		if(operators[i] == '-'){
			numbers[i+1] *= -1;
			operators[i] = '+';
			done = 1;
		}
		if(operators[i] == '/'){
			numbers[i+1] = 1/numbers[i+1];
			operators[i] = '*';
			done = 1;
		}
	}
	if(done){
		printCompleteLineToFile(numbers, operators, numNumbers, destination);
	}
	done = 0;

	for(i=0; i<numNumbers; i++){
		if(operators[i] == '^'){
			numbers[i+1] = pow(numbers[i], numbers[i+1]);
			operators[i] = '*';
			numbers[i] = 1;
			done = 1;
		}
	}
	if(done){
		printStepToFile(numbers, operators, numNumbers, destination);	
	}
	done = 0;

	for(i=0; i<numNumbers; i++){
		if(operators[i] == '*'){
			numbers[i+1] *= numbers[i];
			operators[i] = '+';
			numbers[i] = 0;
			done = 1;
		}
	}
	if(done){
		printStepToFile(numbers, operators, numNumbers, destination);	
	}
		
	final = sumaVector(numbers, numNumbers);
	if(final != numbers[numNumbers - 1]){
		fprintf(destination, "%lf\n", final);
	}
	free(numbers);
	free(operators);

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

double sumaVector(double* vec, int size){
	if(!size){
		return 0;
	}
	return *vec + sumaVector(vec+1, size-1);
}
