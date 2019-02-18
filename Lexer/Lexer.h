#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum LexTypes {
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
        _SYMBOLS = { { '{', LBRA },
            { '}', RBRA },
            { '=', EQUAL },
            { ';', SEMICOLON },
            { '(', LPAR },
            { ')', RPAR },
            { '+', PLUS },
            { '-', MINUS },
            { '<', LESS } };

    map<string, LexTypes>
        _WORDS = { { "if", IF },
            { "else", ELSE },
            { "do", DO },
            { "while", WHILE } };

    std::vector<char>* _words;

public:
    Lexer(const std::vector<char>* words);
    ~Lexer() {};

    void Error(const string& msg);

    vector<TokenStruct> tokenize();
};
