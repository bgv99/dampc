#include "include/vec.h"
#include "include/lexer.h"
#include <ctype.h>
#include <string.h>

Vec *tokenise(char source_code[]) {
    Vec *tokens = Vec_init(sizeof(Token), 0);
    char *buffer = malloc(sizeof(char));
    int source_length = strlen(source_code);
    int buffer_index = 0;
    Token token;

    token.line = 1;
    token.column = 1;

    for(int i = 0; i < source_length; i++) {
        if(isspace(source_code[i])) {
            if(source_code[i] == '\n') {
                token.line++;
                token.column = 1;

                continue;
            }

            token.column++;

            continue;
        }

        if(isalpha(source_code[i])) {
            int k = i;

            while(isalpha(source_code[k])) {
                buffer = realloc(buffer, sizeof(char) * (buffer_index + 1));
                buffer[buffer_index] = source_code[k];

                buffer_index++;
                k++;
                token.column++;
            }

            token.text = strdup(buffer);

            if(strcmp(buffer, "return") == 0) {
                token.type = T_KW_RETURN;

                Vec_push(tokens, &token);
            } else {
                token.type = T_IDENTIFIER;

                Vec_push(tokens, &token);
            }

            memset(buffer, 0, sizeof(char) * (buffer_index + 1));

            buffer_index = 0;
            i = k - 1;

            continue;
        }

        if(isdigit(source_code[i])) {
            int j = i;

            while(isdigit(source_code[j])) {
                buffer = realloc(buffer, sizeof(char) * (buffer_index + 1));
                buffer[buffer_index] = source_code[j];

                buffer_index++;
                j++;
                token.column++;
            }

            token.type = T_LITERAL;
            token.text = strdup(buffer);

            Vec_push(tokens, &token);
            memset(buffer, 0, sizeof(char) * (buffer_index + 1));

            buffer_index = 0;
            i = j - 1;

            continue;
        }

        token.text = strdup(&source_code[i]);
        token.column++;

        switch(source_code[i]) {
            case '=': token.type = T_EQUAL; Vec_push(tokens, &token); break;
            case ';': token.type = T_SEMICOLON; Vec_push(tokens, &token); break;
            case '(': token.type = T_L_ROUND_PARENT; Vec_push(tokens, &token); break;
            case ')': token.type = T_R_ROUND_PARENT; Vec_push(tokens, &token); break;
            case '+': token.type = T_PLUS; Vec_push(tokens, &token); break;
            case '-': token.type = T_MINUS; Vec_push(tokens, &token); break;
            case '*': token.type = T_STAR; Vec_push(tokens, &token); break;
            case '/': token.type = T_SLASH; Vec_push(tokens, &token);
        }
    }

    free(buffer);

    return tokens;
}