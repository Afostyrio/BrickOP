#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "printer.h"

#ifndef PEMDAS_H
#define PEMDAS_H

#define MAX_FILENAME_SIZE 255
#define MAX_OPERATION_SIZE 1000

//FILE* getLineFromFile(char filename[MAX_FILENAME_SIZE]);
void solveLineByLine(char filename[MAX_FILENAME_SIZE]);
int countNumbers(FILE* stream);
//int countOperators(FILE* stream);
double pemdasSolve(char filename[MAX_FILENAME_SIZE]);
double sumaVector(double* vec, int size);
void removeNewline(char* str);
void removeNulChar(char* str);
void clearParen(char filename[MAX_FILENAME_SIZE]);

#endif
