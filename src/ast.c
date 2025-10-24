#include "include/ast.h"

void ast_destroy(AST *ast) {
    if(!ast) {
        return;
    }

    switch(ast->NodeType) {
        case NODE_LITERAL:
            break;
        case NODE_PLUS:
            ast_destroy(ast->Nodes.PlusNode.left);
            ast_destroy(ast->Nodes.PlusNode.right);

            break;
        case NODE_RETURN:
            ast_destroy(ast->Nodes.ReturnNode.expr);

            break;
        case NODE_MAIN:
            ast_destroy(ast->Nodes.MainNode.body);
    }

    free(ast);
}

AST *ast_newLiteralNode(int32_t value) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_LITERAL;
    node->Nodes.LiteralNode.value = value;

    return node;
}

AST *ast_newMainNode(AST *body) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_MAIN;
    node->Nodes.MainNode.body = body;

    return node;
}

AST *ast_newReturnNode(AST *expr) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_RETURN;
    node->Nodes.ReturnNode.expr = expr;

    return node;
}

AST *ast_newPlusNode(AST *left, AST *right) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_PLUS;
    node->Nodes.PlusNode.left = left;
    node->Nodes.PlusNode.right = right;

    return node;
}