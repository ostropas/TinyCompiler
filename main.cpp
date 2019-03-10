#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("No input file\n");
        return -1;
    }
    // TODO: test

    ifstream inFile;
    inFile.open(argv[1]);

    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }

    char tmp;
    vector<char> words = {};

    while (inFile >> tmp) {
        words.emplace_back(tmp);
    }

    inFile.close();

    Lexer lexer = Lexer(words);

    //vector<TokenStruct> tokens = Lexer::Tokenize(words);
    //vector<Node> nodes = Parser::Parse(tokens);

    //Parser parser = Parser();

    return 0;
}
