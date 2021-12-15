#include "screen.h"
#include "pemdas.h"
#include "printer.h"
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[]) {	
	setlocale(LC_ALL,"");
	
	solveLineByLine("test.txt");
	
	getchar();
	return 0;
}
