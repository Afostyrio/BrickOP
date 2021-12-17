#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "printer.h"

#ifndef PEMDAS_H
#define PEMDAS_H

#define MAX_FILENAME_SIZE 255
#define MAX_OPERATION_SIZE 1000

void solveLineByLine(char filename[MAX_FILENAME_SIZE]);
int countNumbers(FILE* stream);
double pemdasSolve(FILE* stream, FILE* destination);
double sumaVector(double* vec, int size);
void clearParen(char filename[MAX_FILENAME_SIZE], FILE* destination);

#endif
