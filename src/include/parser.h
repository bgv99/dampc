#pragma once

#include "ast.h"

AST *expression();
AST *statement();
void consume();
AST *parse();