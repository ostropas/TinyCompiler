#include "Lexer.h"

Lexer::Lexer(const std::vector<std::string> *words)
{
    _words = const_cast<std::vector<std::string> *>(words);
}

void Lexer::EmptyWords()
{
    _words->clear();
}

void Lexer::Error(string msg)
{
    cout << msg << '\n';
    exit(-1);
}