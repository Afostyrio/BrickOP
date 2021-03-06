#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef PRINTER_H
#define PRINTER_H

void printVector(double* vec, int size);
void printCharVector(char* vec, int size);
void printString(char* vec);
void printCompleteLineToFile(double* numbers, char* operators, int size, FILE* destination);
void printStepToFile(double* numbers, char* operators, int size, FILE* destination);

#endif
