#include "screen.h"
#include "pemdas.h"
#include "printer.h"
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[]) {	
	setlocale(LC_ALL,"");
	
	FILE* aux = fopen("test.txt", "r");
	printf("\n%lf", pemdasSolve(aux));

	getchar();
	return 0;
}
