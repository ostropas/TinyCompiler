#include "Parser.h"

shared_ptr<Node> Parser::term()
{
    if (_lexer.getSymbol() == LexTypes::ID) {
        auto n = make_shared<Node>(ParserKind::VAR, _lexer.getValue());
        _lexer.nextTok();
        return move(n);
    } else if (_lexer.getSymbol() == LexTypes::NUM) {
        auto n = make_shared<Node>(ParserKind::CONST, _lexer.getValue());
        _lexer.nextTok();
        return move(n);
    } else {
        return parenExpr();
    }
}

shared_ptr<Node> Parser::test()
{
    auto n = summa();
    if (_lexer.getSymbol() == LexTypes::LESS) {
        _lexer.nextTok();
        n = make_shared<Node>(ParserKind::LT, 0, n, summa());
    }

    return move(n);
}

shared_ptr<Node> Parser::summa()
{
    auto n = term();
    while (_lexer.getSymbol() == LexTypes::PLUS || _lexer.getSymbol() == LexTypes::MINUS) {
        if (_lexer.getSymbol() == LexTypes::PLUS) {
            n->kind = ParserKind::ADD;
        } else {
            n->kind = ParserKind::SUB;
        }
        _lexer.nextTok();
        n = make_shared<Node>(n->kind, 0, n, term());
    }

    return move(n);
}

shared_ptr<Node> Parser::expr()
{
    if (_lexer.getSymbol() != LexTypes::ID) {
        return test();
    }
    auto n = test();
    if (n->kind == ParserKind::VAR && _lexer.getSymbol() == LexTypes::EQUAL) {
        _lexer.nextTok();
        n = make_shared<Node>(ParserKind::SET, 0, n, expr());
    }

    return move(n);
}

shared_ptr<Node> Parser::parenExpr()
{
    if (_lexer.getSymbol() != LexTypes::LPAR) {
        error("\"(\" expected");
    }
    _lexer.nextTok();
    auto n = expr();
    if (_lexer.getSymbol() != LexTypes::RPAR) {
        error("\")\" expected");
    }
    _lexer.nextTok();
    return move(n);
}

shared_ptr<Node> Parser::statement()
{
    shared_ptr<Node> n;
    switch (_lexer.getSymbol()) {
    case LexTypes::IF:
        n = make_unique<Node>(ParserKind::IF1);
        _lexer.nextTok();
        n->op1 = parenExpr();
        n->op2 = statement();
        if (_lexer.getSymbol() == LexTypes::ELSE) {
            n->kind = ParserKind::IF2;
            _lexer.nextTok();
            n->op3 = statement();
        }
        break;
    case LexTypes::WHILE:
        n = make_unique<Node>(ParserKind::WHILE);
        _lexer.nextTok();
        n->op1 = parenExpr();
        n->op2 = statement();
        break;
    case LexTypes::DO:
        n = make_unique<Node>(ParserKind::DO);
        _lexer.nextTok();
        n->op1 = statement();
        if (_lexer.getSymbol() != LexTypes::WHILE) {
            error("\"while\" expected");
        }
        _lexer.nextTok();
        n->op2 = parenExpr();
        if (_lexer.getSymbol() != LexTypes::SEMICOLON) {
            error("\";\" expected");
        }
        break;
    case LexTypes::SEMICOLON:
        n = make_unique<Node>(ParserKind::EMPTY);
        _lexer.nextTok();
        break;
    case LexTypes::LBRA:
        n = make_unique<Node>(ParserKind::EMPTY);
        _lexer.nextTok();
        while (_lexer.getSymbol() != LexTypes::RBRA) {
            n = make_unique<Node>(ParserKind::SEQ, 0, n, statement());
        }
        _lexer.nextTok();
        break;
    default:
        n = make_unique<Node>(ParserKind::EXPR, 0, expr());
        if (_lexer.getSymbol() != LexTypes::SEMICOLON) {
            error("\";\" expected");
        }
        _lexer.nextTok();
        break;
    }

    return move(n);
}

shared_ptr<Node> Parser::createNode()
{
    auto node = make_unique<Node>(ParserKind::PROG, 0, statement());
    if (_lexer.getSymbol() != LexTypes::EOF) {
        error("Invalid statement syntax");
    }
    return node;
}

void Parser::error(const string& msg)
{
    cout << msg << '\n';
    exit(-1);
}
