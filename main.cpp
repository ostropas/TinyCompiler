#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Compiler/Compiler.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "VirtualMachine/VirtualMachine.h"

using namespace std;

int main(int argc, char** argv)
{
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

    char tmp;
    vector<char> words = {};

    while (inFile >> tmp) {
        words.emplace_back(tmp);
    }

    inFile.close();

    Lexer lexer = Lexer(words);
    shared_ptr<Node> node = Parser(lexer).CreateNode();
    Compiler compiler = Compiler();
    auto programm = compiler.Ñompile(node);

    VirtualMachine vm = VirtualMachine();
    vm.Run(programm);

    return 0;
}
