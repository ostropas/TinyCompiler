#pragma once
#include "../Lexer/Lexer.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/// <summary>
/// All possible parser kinds
/// </summary>
enum class ParserKind {
    VAR,
    CONST,
    ADD,
    SUB,
    LT,
    SET,
    IF1,
    IF2,
    WHILE,
    DO,
    EMPTY,
    SEQ,
    EXPR,
    PROG
};

/// <summary>
/// Parser struct in tree, Node is realisation of tree
/// </summary>
class Node {
public:
    ParserKind kind;
    int value;
    // Next tree leafs
    shared_ptr<Node> op1;
    shared_ptr<Node> op2;
    shared_ptr<Node> op3;

    Node(){};
    Node(ParserKind kind, int value = NULL, shared_ptr<Node> op1 = nullptr, shared_ptr<Node> op2 = nullptr, shared_ptr<Node> op3 = nullptr)
    {

        this->kind = kind;
        this->value = value;
        this->op1 = move(op1);
        this->op2 = move(op2);
        this->op3 = move(op3);
    }
};

class Parser {
public:
    Parser(){};
    Parser(Lexer lexer)
    {
        _lexer = lexer;
        _currentIndex = 0;
    };
    ~Parser(){};

    Node CreateNode();

    //vector<Node> Parse(vector<TokenStruct> tokens);

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
