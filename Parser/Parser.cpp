#include "Parser.h"

Node* Parser::Term()
{
    if (_lexer.Sym() == LexTypes::ID) {
        auto n = new Node(ParserKind::VAR, _lexer.Value());
        _lexer.NextTok();
        return n;
    } else if (_lexer.Sym() == LexTypes::NUM) {
        auto n = new Node(ParserKind::CONST, _lexer.Value());
        _lexer.NextTok();
        return n;
    } else {
        return ParenExpr();
    }
}

Node* Parser::Test()
{
    auto n = Summa();
    if (_lexer.Sym() == LexTypes::LESS) {
        _lexer.NextTok();
        n = new Node(ParserKind::LT, 0, n, Summa());
    }

    return n;
}

Node* Parser::Summa()
{
    auto n = Term();
    while (_lexer.Sym() == LexTypes::PLUS || _lexer.Sym() == LexTypes::MINUS) {
        if (_lexer.Sym() == LexTypes::PLUS) {
            n->kind = ParserKind::ADD;
        } else {
            n->kind = ParserKind::SUB;
        }
        _lexer.NextTok();
        n = new Node(n->kind, 0, n, Term());
    }

    return n;
}

Node* Parser::Expr()
{
    if (_lexer.Sym() != LexTypes::ID) {
        return Test();
    }
    auto n = Test();
    if (n->kind == ParserKind::VAR && _lexer.Sym() == LexTypes::EQUAL) {
        _lexer.NextTok();
        n = new Node(ParserKind::SET, 0, n, Expr());
    }

    return n;
}

Node* Parser::ParenExpr()
{
    if (_lexer.Sym() != LexTypes::LPAR) {
        Error("\"(\" expected");
    }
    _lexer.NextTok();
    Node* n = Expr();
    if (_lexer.Sym() != LexTypes::RPAR) {
        Error("\")\" expected");
    }
    _lexer.NextTok();
    return n;
}

Node* Parser::Statement()
{
    Node* n;
    switch (_lexer.Sym()) {
    case LexTypes::IF:
        n = new Node(ParserKind::IF1);
        _lexer.NextTok();
        n->op1 = ParenExpr();
        n->op2 = Statement();
        if (_lexer.Sym() == LexTypes::ELSE) {
            n->kind = ParserKind::IF2;
            _lexer.NextTok();
            n->op3 = Statement();
        }
        break;
    case LexTypes::WHILE:
        n = new Node(ParserKind::WHILE);
        _lexer.NextTok();
        n->op1 = ParenExpr();
        n->op2 = Statement();
        break;
    case LexTypes::DO:
        n = new Node(ParserKind::DO);
        _lexer.NextTok();
        n->op1 = Statement();
        if (_lexer.Sym() != LexTypes::WHILE) {
            Error("\"while\" expected");
        }
        _lexer.NextTok();
        n->op2 = ParenExpr();
        if (_lexer.Sym() != LexTypes::SEMICOLON) {
            Error("\";\" expected");
        }
        break;
    case LexTypes::SEMICOLON:
        n = new Node(ParserKind::EMPTY);
        _lexer.NextTok();
        break;
    case LexTypes::LBRA:
        n = new Node(ParserKind::EMPTY);
        _lexer.NextTok();
        while (_lexer.Sym() != LexTypes::RBRA) {
            n = new Node(ParserKind::SEQ, 0, n, Statement());
        }
        _lexer.NextTok();
        break;
    default:
        n = new Node(ParserKind::EXPR, 0, Expr());
        if (_lexer.Sym() != LexTypes::SEMICOLON) {
            Error("\";\" expected");
        }
        _lexer.NextTok();
        break;
    }

    return n;
}

Node Parser::CreateNode()
{
    // TODO: think about destructor
    Node node = Node(ParserKind::PROG, 0, Statement());
    if (_lexer.Sym() != LexTypes::EOF) {
        Error("Invalid statement syntax");
    }
    return node;
}

void Parser::Error(const string& msg)
{
    cout << msg << '\n';
    exit(-1);
}
