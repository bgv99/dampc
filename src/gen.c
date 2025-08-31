#include "include/gen.h"
#include "include/ast.h"
#include <stdio.h>

extern FILE *output_file;

void generateAsm(AST *ast) {
    if(ast) {
        switch(ast->NodeType) {
            case NODE_MAIN:
                fprintf(output_file, "global _start\n");
                fprintf(output_file, "_start:\n");
                generateAsm(ast->Nodes.MainNode.body);

                break;
            case NODE_RETURN:
                generateAsm(ast->Nodes.ReturnNode.expr);
                fprintf(output_file, "\tmov rdi, rax\n");
                fprintf(output_file, "\tmov rax, 60\n");
                fprintf(output_file, "\tsyscall\n");

                break;
            case NODE_LITERAL:
                fprintf(output_file, "\tmov rax, %d\n", ast->Nodes.LiteralNode.value);

                break;
            case NODE_PLUS:
                generateAsm(ast->Nodes.PlusNode.left);
                fprintf(output_file, "\tpush rax\n");
                generateAsm(ast->Nodes.PlusNode.right);
                fprintf(output_file, "\tpop rbx\n");
                fprintf(output_file, "\tadd rax, rbx\n");
        }
    }
}