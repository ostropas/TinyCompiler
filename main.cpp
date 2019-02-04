// Compiler modules
// Other includes
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Lexer/Lexer.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("No input file\n");
		return -1;
	}

	ifstream inFile;
	inFile.open(argv[1]);

	if (!inFile) {
		cout << "Unable to open file";
		exit(1);
	}

	string tmp;
	vector <string> words = {};
	

	while (inFile >> tmp) {
		words.emplace_back(tmp);
		// cout << m;
	}

	inFile.close();

        Lexer lexer = Lexer(words);
	// `vector <string> tokens = lexer.tokenize();
	for (int i = 0; i < lexer._words->size(); i++) {
	cout << "kek";
	}
	// cout << lexer.bar().c_str() << '\n';
	
	return 0;
}

