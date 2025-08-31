#pragma once

typedef struct AST AST;

struct AST {
    enum {
        NODE_RETURN = 0,
        NODE_PLUS = 1,
        NODE_LITERAL = 2,
        NODE_MAIN = 3
    } NodeType;

    union {
        struct LiteralNode { int value; } LiteralNode;
        struct PlusNode { AST *left; AST *right; } PlusNode;
        struct ReturnNode { AST *expr; } ReturnNode;
        struct MainNode { AST *body; } MainNode;
    } Nodes;
};

void AST_destroy(AST *);
AST *newLiteralNode(int _value);
AST *newMainNode(AST *_body);
AST *newReturnNode(AST *_expr);
AST *newPlusNode(AST *_left, AST *_right);