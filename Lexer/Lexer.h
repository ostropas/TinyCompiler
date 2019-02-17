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

struct CharStruct {
    LexTypes type;
    char ch;
    string value;
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

    std::vector<std::string>* _words;

public:
    void Error(const string& msg);

    Lexer(const std::vector<std::string>* words);
    ~Lexer() {};

    void EmptyWords();

    // const std::string& bar() const { return _bar; }
    // void bar(const std::string& bar) { _bar = bar; }
};
