// Compiler modules
// Other includes
#include <stdio.h>

#include "Lexer/Lexer.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("No input msg\n");
		return -1;
	}

	Lexer lexer = Lexer();
	lexer.bar("wow");

	printf(lexer.bar().c_str());


	return 0;
}

