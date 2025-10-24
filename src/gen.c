#include "include/gen.h"

void gen_asm(AST *ast, FILE *output_file) {
    if(!ast) {
        return;
    }

    switch(ast->NodeType) {
        case NODE_MAIN:
            fprintf(output_file, "global _start\n");
            fprintf(output_file, "_start:\n");
            gen_asm(ast->Nodes.MainNode.body, output_file);

            break;
        case NODE_RETURN:
            gen_asm(ast->Nodes.ReturnNode.expr, output_file);
            fprintf(output_file, "\tmov rdi, rax\n");
            fprintf(output_file, "\tmov rax, 60\n");
            fprintf(output_file, "\tsyscall\n");

            break;
        case NODE_LITERAL:
            fprintf(output_file, "\tmov rax, %d\n", ast->Nodes.LiteralNode.value);

            break;
        case NODE_PLUS:
            gen_asm(ast->Nodes.PlusNode.left, output_file);
            fprintf(output_file, "\tpush rax\n");
            gen_asm(ast->Nodes.PlusNode.right, output_file);
            fprintf(output_file, "\tpop rbx\n");
            fprintf(output_file, "\tadd rax, rbx\n");
    }
}