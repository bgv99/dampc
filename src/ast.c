#include "include/ast.h"
#include <stdlib.h>

AST *ast;

void AST_destroy(AST *ast) {
    if(ast) {
        switch(ast->NodeType) {
            case NODE_LITERAL:
                break;
            case NODE_PLUS:
                AST_destroy(ast->Nodes.PlusNode.left);
                AST_destroy(ast->Nodes.PlusNode.right);

                break;
            case NODE_RETURN:
                AST_destroy(ast->Nodes.ReturnNode.expr);

                break;
            case NODE_MAIN:
                AST_destroy(ast->Nodes.MainNode.body);
        }

        free(ast);
    }
}

AST *newLiteralNode(int _value) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_LITERAL;
    node->Nodes.LiteralNode.value = _value;

    return node;
}

AST *newMainNode(AST *_body) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_MAIN;
    node->Nodes.MainNode.body = _body;

    return node;
}

AST *newReturnNode(AST *_expr) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_RETURN;
    node->Nodes.ReturnNode.expr = _expr;

    return node;
}

AST *newPlusNode(AST *_left, AST *_right) {
    AST *node = malloc(sizeof(AST));

    node->NodeType = NODE_PLUS;
    node->Nodes.PlusNode.left = _left;
    node->Nodes.PlusNode.right = _right;

    return node;
}