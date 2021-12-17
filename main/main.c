#include "pemdas.h"
#include <locale.h>

int main(int argc, char *argv[]) {	
	setlocale(LC_ALL,"");
	
	solveLineByLine("operaciones.txt");
	
	getchar();
	return 0;
}
