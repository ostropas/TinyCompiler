#ifndef PARSER_H
#define PARSER_H
#include "../Lexer/Lexer.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace parser {
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
}

struct Node {
    parser::ParserKind kind;
    int value;
    // TODO: op1, op2, op3 - type? (maybe function?)
    /*TokenStruct(LexTypes type, int value)
	{
		this->type = type;
		this->value = value;
	}*/
};

class Parser {
public:
    Parser() {};
    Parser(const std::vector<TokenStruct>* tokens);
    ~Parser() {};

private:
    vector<TokenStruct> _tokens;

    void Error(const string& msg);
};
#endif // !PARSER_H
