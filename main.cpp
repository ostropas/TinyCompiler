#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Lexer/Lexer.h"

// #include "CharStruct.h"

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

    string tmp;
    vector<string> words = {};

    while (inFile >> tmp) {
        words.emplace_back(tmp);
    }

    inFile.close();

    Lexer lexer = Lexer(&words);
    // lexer.Error("kek");

    for (int i = 0; i < words.size(); i++) {
        cout << words[i];
    }
    // cout << lexer.bar().c_str() << '\n';

    return 0;
}
