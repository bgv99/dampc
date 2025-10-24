#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "vec.h"
#include "log.h"
#include <stdlib.h>

typedef struct {
    size_t token_index;
    Token *current_token;
    Vec *tokens;
    AST *ast;
} Parser;

AST *parser_expression(Parser *p);
AST *parser_statement(Parser *p);
void parser_consume(Parser *p);
AST *parser_parse(Parser *p);

#endif
