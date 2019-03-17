#include "Lexer.h"

const map<char, LexTypes> Lexer::_SYMBOLS = { { '{', LexTypes::LBRA },
    { '}', LexTypes::RBRA },
    { '=', LexTypes::EQUAL },
    { ';', LexTypes::SEMICOLON },
    { '(', LexTypes::LPAR },
    { ')', LexTypes::RPAR },
    { '+', LexTypes::PLUS },
    { '-', LexTypes::MINUS },
    { '<', LexTypes::LESS } };

const map<string, LexTypes> Lexer::_WORDS = { { "if", LexTypes::IF },
    { "else", LexTypes::ELSE },
    { "do", LexTypes::DO },
    { "while", LexTypes::WHILE } };

void Lexer::Error(const string& msg)
{
    cout << msg << '\n';
    exit(-1);
}

Lexer::Lexer(const std::vector<char>& words)
{
    uint64_t index = 0;
    _Tokens = vector<TokenStruct>();

    while (index < words.size()) {
        char currentChar = words.at(index);
        if (_SYMBOLS.find(currentChar) != _SYMBOLS.end()) {
            _Tokens.emplace_back(TokenStruct(_SYMBOLS.at(currentChar), -1));
            index++;
        } else if (isdigit(currentChar)) {
            int intVal = 0;
            while (isdigit(currentChar)) {
                intVal = intVal * 10 + (static_cast<int>(currentChar) - 48);
                currentChar = words.at(++index);
            }

            _Tokens.emplace_back(TokenStruct(LexTypes::NUM, intVal));
        } else if (isalpha(currentChar)) {
            string ident = "";
            while (isalpha(currentChar)) {
                ident += currentChar;
                if (index == words.size() - 1) {
                    ++index;
                    break;
                }
                currentChar = words.at(++index);
            }

            if (_WORDS.find(ident) != _WORDS.end()) {
                _Tokens.emplace_back(TokenStruct(_WORDS.at(ident), -1));
            } else if (ident.size() == 1) {
                _Tokens.emplace_back(TokenStruct(LexTypes::ID, static_cast<int>(ident.at(0) - 'a')));
            } else {
                Error("Unknown identifier: " + ident);
            }
        } else {
            index++;
        }
    }

    _Tokens.emplace_back(TokenStruct(LexTypes::EOF, -1));
    _CurrentTokIndex = 0;
}

void Lexer::NextTok() const
{
    ++_CurrentTokIndex;
}

int Lexer::Value() const
{
    if (_CurrentTokIndex + 1 < _Tokens.size()) {
        return _Tokens[_CurrentTokIndex].value;
    }

    return -1;
}

LexTypes const& Lexer::Sym() const
{
    if (_CurrentTokIndex + 1 < _Tokens.size()) {
        return _Tokens[_CurrentTokIndex].type;
    }

    return LexTypes::EOF;
}
