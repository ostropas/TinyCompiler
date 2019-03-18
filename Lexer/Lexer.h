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
    static void error(const string& msg);

    mutable size_t _currentTokIndex = 0;
    vector<TokenStruct> _tokens = vector<TokenStruct>();

public:
    Lexer() {};
    Lexer(const std::vector<char>& words);
    ~Lexer() {};
    void nextTok() const;
    int getValue() const;
    LexTypes const& getSymbol() const;
};
