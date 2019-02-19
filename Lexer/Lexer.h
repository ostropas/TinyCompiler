#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class LexTypes {
    NUM,
    ID,
    IF,
    ELSE,
    WHILE,
    DO,
    LBRA,
    RBRA,
    LPAR,
    RPAR,
    PLUS,
    MINUS,
    LESS,
    EQUAL,
    SEMICOLON
};

struct TokenStruct {
    LexTypes type;
    int value;
    TokenStruct(LexTypes type, int value)
    {
        this->type = type;
        this->value = value;
    }
};

class Lexer {
private:
    map<char, LexTypes>
        _SYMBOLS = { { '{', LexTypes::LBRA },
            { '}', LexTypes::RBRA },
            { '=', LexTypes::EQUAL },
            { ';', LexTypes::SEMICOLON },
            { '(', LexTypes::LPAR },
            { ')', LexTypes::RPAR },
            { '+', LexTypes::PLUS },
            { '-', LexTypes::MINUS },
            { '<', LexTypes::LESS } };

    map<string, LexTypes>
        _WORDS = { { "if", LexTypes::IF },
            { "else", LexTypes::ELSE },
            { "do", LexTypes::DO },
            { "while", LexTypes::WHILE } };

    std::vector<char>* _words;

    void Error(const string& msg);

public:
    Lexer(const std::vector<char>* words);
    ~Lexer() {};

    vector<TokenStruct> tokenize();
};
#endif // !LEXER_H
