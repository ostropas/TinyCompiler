#pragma once
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
    /// <summary>
    /// All posible lexer symbols
    /// </summary>
    static const map<char, LexTypes> _SYMBOLS;
    /// <summary>
    /// All keywords
    /// </summary>
    static const map<string, LexTypes> _WORDS;

    /// <summary>
    /// Print error
    /// </summary>
    /// <param name="msg"></param>
    static void Error(const string& msg);

public:
    Lexer() {};
    ~Lexer() {};

    /// <summary>
    /// Create token from text
    /// </summary>
    /// <param name="words">input text</param>
    /// <returns>tokens</returns>
    static vector<TokenStruct> tokenize(const std::vector<char>& words);
};
