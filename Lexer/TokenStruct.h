#pragma once

#undef EOF

enum class LexTypes {
    NUM,
    ID,
    IF,
    ELSE,
    WHILE,
    DO,
    LBRA,
    RBRA,
    LPAR,
    RPAR,
    PLUS,
    MINUS,
    LESS,
    EQUAL,
    SEMICOLON,
    EOF
};

struct TokenStruct {
    LexTypes type;
    int value;
    TokenStruct(LexTypes type, int value)
    {
        this->type = type;
        this->value = value;
    }
};