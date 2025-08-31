#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/vec.h"
#include "include/log.h"
#include "include/gen.h"
#include "include/ast.h"

extern AST *ast;

char *filename;
Vec *tokens;
FILE *output_file;

int extensionCheck(char *filename) {
    char *ext = strrchr(filename, '.');

    if(!ext) {
        return -1;
    } else if(strcmp(ext, ".damp") == 0) {
        return 0;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        _log(INFO, "Usage: dampc <file.damp>");

        return EXIT_FAILURE;
    }

    if(extensionCheck(argv[1]) != 0) {
        _log(ERR, "Invalid Damp file!");

        return EXIT_FAILURE;
    }

    #if !defined (__linux__) && !defined (__x86_64__)
        _log(INFO, "Unsupported platform.");

        return EXIT_FAILURE;
    #endif

    FILE *source_file = fopen(argv[1], "r");
    char *source_code = malloc(sizeof(char));

    filename = argv[1];

    for(int i = 0, c; (c = fgetc(source_file)) != EOF; i++) {
        source_code = realloc(source_code, sizeof(char) * (i + 1));
        source_code[i] = c;
    }

    tokens = tokenise(source_code);

    if(Vec_length(tokens) > 0) {
        parse();

        output_file = fopen("out.asm", "w");

        generateAsm(ast);
        fclose(output_file);
        system("nasm -f elf64 out.asm && ld -o out out.o");
    } else {
        _log(INFO, "There is nothing to do.");
    }

    free(source_code);
    Vec_destroy(tokens);
    fclose(source_file);
    AST_destroy(ast);

    return EXIT_SUCCESS;
}