#include "Lexer.h"

Lexer::Lexer(const std::vector<char>* words)
{
    _words = const_cast<std::vector<char>*>(words);
}

void Lexer::Error(const string& msg)
{
    cout << msg << '\n';
    exit(-1);
}

vector<TokenStruct> Lexer::tokenize()
{
    uint64_t index = 0;
    vector<TokenStruct> tokens = vector<TokenStruct>();

    while (index < _words->size()) {
        char currentChar = _words->at(index);
        if (_SYMBOLS.find(currentChar) != _SYMBOLS.end()) {
            tokens.emplace_back(TokenStruct(_SYMBOLS.at(currentChar), -1));
            index++;
        } else if (isdigit(currentChar)) {
            int intVal = 0;
            while (isdigit(currentChar)) {
                intVal = intVal * 10 + (static_cast<int>(currentChar) - 48);
                currentChar = _words->at(++index);
            }

            tokens.emplace_back(TokenStruct(NUM, intVal));
        } else if (isalpha(currentChar)) {
            string ident = "";
            while (isalpha(currentChar)) {
                ident = currentChar;
                currentChar = _words->at(++index);
            }

            if (_WORDS.find(ident) != _WORDS.end()) {
                tokens.emplace_back(TokenStruct(_WORDS.at(ident), -1));
            } else if (ident.size() == 1) {
                tokens.emplace_back(TokenStruct(ID, static_cast<int>(ident.at(0) - 'a')));
            } else {
                Error("Unknown identifier: " + ident);
            }
        } else {
            index++;
        }
    }
    return tokens;
}
