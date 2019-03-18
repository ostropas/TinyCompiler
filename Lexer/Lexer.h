#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "TokenStruct.h"

using namespace std;

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

    mutable size_t _CurrentTokIndex = 0;
    vector<TokenStruct> _Tokens = vector<TokenStruct>();

public:
    Lexer() {};
    Lexer(const std::vector<char>& words);
    ~Lexer() {};
    void NextTok() const;
    int Value() const;
    LexTypes const& Sym() const;
};
