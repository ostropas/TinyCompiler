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
    Node* op1;
    Node* op2;
    Node* op3;

    Node() {};
    Node(ParserKind kind, int value = NULL, Node* op1 = nullptr, Node* op2 = nullptr, Node* op3 = nullptr)
    {

        this->kind = kind;
        this->value = value;
        this->op1 = op1;
        this->op2 = op2;
        this->op3 = op3;
    }
    // TODO: node is dynamic, need to create dynamic
    ~Node();
};

class Parser {
public:
    Parser() {};
    Parser(Lexer lexer)
    {
        _lexer = lexer;
        _currentIndex = 0;
    };
    ~Parser() {};

    Node CreateNode();

    vector<Node> Parse(vector<TokenStruct> tokens);

private:
    Node* Statement();
    Node* ParenExpr();
    Node* Expr();
    Node* Test();
    Node* Summa();
    Node* Term();
    size_t _currentIndex;
    Lexer _lexer;

private:
    void Error(const string& msg);
};
