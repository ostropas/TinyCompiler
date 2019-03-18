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

    shared_ptr<Node> createNode();

private:
    shared_ptr<Node> statement();
    shared_ptr<Node> parenExpr();
    shared_ptr<Node> expr();
    shared_ptr<Node> test();
    shared_ptr<Node> summa();
    shared_ptr<Node> term();
    size_t _currentIndex;
    Lexer _lexer;

private:
    void error(const string& msg);
};
