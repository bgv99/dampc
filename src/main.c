#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/vec.h"
#include "include/log.h"
#include "include/gen.h"

Vec *logs;

int32_t main_validateSource(char *filename) {
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
    logs = vec_init(sizeof(Log), 0);

    if(argc != 2) {
        log_new(logs, (Log) {
            .level = INFO,
            .type = USAGE_ERROR
        });

        log_flush(logs);

        return EXIT_FAILURE;
    }

    if(main_validateSource(argv[1]) != 0) {
        log_new(logs, (Log) {
            .level = INFO,
            .type = INVALID_SOURCE
        });

        log_flush(logs);

        return EXIT_FAILURE;
    }

    char *source_filename = argv[1];
    FILE *source_file = fopen(source_filename, "r");
    char *source_code = malloc(sizeof(char));
    FILE *output_file;
    Parser p;
    char c;

    for(size_t i = 0; (c = fgetc(source_file)) != EOF; i++) {
        source_code = realloc(source_code, sizeof(char) * (i + 1));
        source_code[i] = c;
    }

    p.tokens = lexer_tokenise(source_code);

    if(vec_length(p.tokens) > 0) {
        output_file = fopen("out.asm", "w");

        gen_asm(parser_parse(&p), output_file);
        fclose(output_file);
        system("nasm -f elf64 out.asm && ld -o out out.o");
    } else {
        log_new(logs, (Log) {
            .level = INFO,
            .type = BLANK_SOURCE
        });
    }

    free(source_code);
    vec_destroy(p.tokens);
    fclose(source_file);
    log_flush(logs);

    return EXIT_SUCCESS;
}