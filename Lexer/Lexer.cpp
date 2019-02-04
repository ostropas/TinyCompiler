#include "Lexer.h"

Lexer::Lexer(const std::vector<std::string>& words) {
    _words = const_cast<std::vector<std::string>&>(words);
}
