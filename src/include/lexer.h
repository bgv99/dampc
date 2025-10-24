#ifndef LEXER_H
#define LEXER_H

#include "vec.h"
#include "str.h"
#include "log.h"
#include <ctype.h>
#include <string.h>

typedef enum {
    T_IDENTIFIER,
    T_LITERAL,
    T_SEMICOLON,
    T_EQUAL,
    T_L_ROUND_PARENT,
    T_R_ROUND_PARENT,
    T_KW_RETURN,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH
} TokenType;

typedef struct {
    TokenType type;
    char *text;
} Token;

Vec *lexer_tokenise(char source_code[]);

#endif