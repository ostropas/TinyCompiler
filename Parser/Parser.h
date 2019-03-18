#pragma once
#include "../Lexer/Lexer.h"
#include "NodeStruct.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Parser {
public:
    Parser(Lexer lexer)
    {
        _lexer = move(lexer);
        _currentIndex = 0;
    };
    ~Parser() {};

    shared_ptr<Node> CreateNode();

private:
    shared_ptr<Node> Statement();
    shared_ptr<Node> ParenExpr();
    shared_ptr<Node> Expr();
    shared_ptr<Node> Test();
    shared_ptr<Node> Summa();
    shared_ptr<Node> Term();
    size_t _currentIndex;
    Lexer _lexer;

private:
    void Error(const string& msg);
};
