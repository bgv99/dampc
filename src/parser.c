#include "include/parser.h"

AST *parser_expression(Parser *p) {
    AST *left = NULL;
    AST *right = NULL;

    if(p->current_token->type == T_LITERAL) {
        left = ast_newLiteralNode(strtol(p->current_token->text, NULL, 10));

        parser_consume(p);
    } else {
        log_new(logs, (Log) {
            .level = ERR,
            .type = EXPECTED_LITERAL
        });
    }

    while(p->current_token->type == T_PLUS) {
        parser_consume(p);

        if(p->current_token->type == T_LITERAL) {
            right = ast_newLiteralNode(strtol(p->current_token->text, NULL, 10));
            left = ast_newPlusNode(left, right);
        } else {
            log_new(logs, (Log) {
                .level = ERR,
                .type = EXPECTED_LITERAL
            });

            break;
        }

        parser_consume(p);
    }

    if(p->current_token->type != T_SEMICOLON) {
        log_new(logs, (Log) {
            .level = ERR,
            .type = EXPECTED_SEMICOLON
        });
    }

    return left;
}

AST *parser_statement(Parser *p) {
    AST *node = NULL;

    if(p->current_token->type == T_KW_RETURN) {
        parser_consume(p);

        node = ast_newReturnNode(parser_expression(p));
    } else {
        log_new(logs, (Log) {
            .level = ERR,
            EXPECTED_RETURN
        });

        parser_expression(p);
    }

    return node;
}

void parser_consume(Parser *p) {
    if(vec_length(p->tokens) > p->token_index && (vec_get(p->tokens, p->token_index + 1))) {
        p->token_index++;
        p->current_token = vec_get(p->tokens, p->token_index);
    }
}

AST *parser_parse(Parser *p) {
    p->token_index = 0;
    p->current_token = vec_get(p->tokens, p->token_index);
    p->ast = malloc(sizeof(AST));
    p->ast->NodeType = NODE_MAIN;
    p->ast->Nodes.MainNode.body = parser_statement(p);

    return p->ast;
}