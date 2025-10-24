#ifndef GEN_H
#define GEN_H

#include "ast.h"
#include <stdio.h>

void gen_asm(AST *ast, FILE *output_file);

#endif