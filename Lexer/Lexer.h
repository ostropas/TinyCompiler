#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#undef EOF

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
    SEMICOLON,
    EOF
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

    mutable size_t _CurrentTokIndex;
    vector<TokenStruct> _Tokens;

public:
    Lexer() {};
    Lexer(const std::vector<char>& words);
    ~Lexer() {};
    void NextTok() const;
    int const& Value() const;
    LexTypes const& Sym() const;
};
