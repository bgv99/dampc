#pragma once

#include "vec.h"

typedef enum {
    T_IDENTIFIER = 0,
    T_LITERAL = 1,
    T_SEMICOLON = 2,
    T_EQUAL = 3,
    T_L_ROUND_PARENT = 4,
    T_R_ROUND_PARENT = 5,
    T_KW_RETURN = 6,
    T_PLUS = 7,
    T_MINUS = 8,
    T_STAR = 9,
    T_SLASH = 10,
    T_NONE = 11
} TokenType;

typedef struct {
    TokenType type;
    char *text;
    int line;
    int column;
} Token;

Vec *tokenise(char []);