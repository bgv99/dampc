#include "include/parser.h"
#include "include/vec.h"
#include "include/lexer.h"
#include "include/ast.h"
#include "include/log.h"
#include <stdlib.h>

extern Vec *tokens;
extern AST *ast;

int t_index = 0;
Token *t;

AST *expression() {
    AST *left = NULL;
    AST *right = NULL;

    if(t->type == T_LITERAL) {
        left = newLiteralNode(atoi(t->text));

        consume();

        if(t->type == T_SEMICOLON) {
            return left;
        }
    } else {
        _log(ERR, "Expected a literal value.");
        exit(EXIT_FAILURE);
    }

    if(t->type == T_PLUS) {
        consume();

        if(t->type == T_LITERAL) {
            right = newLiteralNode(atoi(t->text));
            left = newPlusNode(left, right);

            consume();

            if(t->type != T_SEMICOLON) {
                _log(ERR, "Expected a semicolon.");
                exit(EXIT_FAILURE);
            }
        } else {
            _log(ERR, "Expected a literal value.");
            exit(EXIT_FAILURE);
        }
    } else {
        _log(ERR, "Expected an operator.");
        exit(EXIT_FAILURE);
    }

    return left;
}

AST *statement() {
    AST *node = NULL;

    if(t->type == T_KW_RETURN) {
        consume();

        node = newReturnNode(expression());
    } else {
        _log(ERR, "Expected return, found '%s'.", t->text);
        exit(EXIT_FAILURE);
    }

    return node;
}

void consume() {
    if(Vec_length(tokens) > t_index && (Vec_get(tokens, t_index + 1))) {
        t_index++;

        t = Vec_get(tokens, t_index);
    }
}

void parse() {
    t = Vec_get(tokens, t_index);
    ast = malloc(sizeof(AST));
    ast->NodeType = NODE_MAIN;
    ast->Nodes.MainNode.body = statement();
}