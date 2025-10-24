#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdint.h>

typedef struct AST AST;

struct AST {
    enum {
        NODE_RETURN,
        NODE_PLUS,
        NODE_LITERAL,
        NODE_MAIN
    } NodeType;

    union {
        struct LiteralNode { int32_t value; } LiteralNode;
        struct PlusNode { AST *left; AST *right; } PlusNode;
        struct ReturnNode { AST *expr; } ReturnNode;
        struct MainNode { AST *body; } MainNode;
    } Nodes;
};

void ast_destroy(AST *ast);
AST *ast_newLiteralNode(int32_t value);
AST *ast_newMainNode(AST *body);
AST *ast_newReturnNode(AST *expr);
AST *ast_newPlusNode(AST *left, AST *right);

#endif