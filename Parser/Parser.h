#ifndef PARSER_H
#define PARSER_H
#include "../Lexer/Lexer.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

//namespace parser {
//enum class ParserKind {
//    VAR,
//    CONST,
//    ADD,
//    SUB,
//    LT,
//    SET,
//    IF1,
//    IF2,
//    WHILE,
//    DO,
//    EMPTY,
//    SEQ,
//    EXPR,
//    PROG
//};
//}
//
//class Node {
//    parser::ParserKind kind;
//    int value;
//    function<int()> op1;
//    function<int()> op2;
//    function<int()> op3;
//
//public:
//    Node(parser::ParserKind kind, int value = NULL, function<int()> op1 = NULL, function<int()> op2 = NULL, function<int()> op3 = NULL)
//    {
//
//        this->kind = kind;
//        this->value = value;
//        this->op1 = op1;
//        this->op2 = op2;
//        this->op3 = op3;
//    }
//};
//
//class Parser {
//public:
//    Parser() {};
//    ~Parser() {};
//
//    static vector<Node> Parse(vector<TokenStruct> tokens);
//
//private:
//    static int _Statement();
//    static size_t _CurrentIndex;
//
//private:
//    void Error(const string& msg);
//};
#endif // !PARSER_H
