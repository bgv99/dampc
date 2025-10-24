#include "include/lexer.h"

Vec *lexer_tokenise(char source_code[]) {
    Vec *tokens = vec_init(sizeof(Token), 0);
    char *buffer = malloc(sizeof(char));

    if(!tokens || !buffer) {
        return NULL;
    }

    size_t source_length = strlen(source_code);
    size_t buffer_index = 0;
    Token token;

    for(size_t i = 0; i < source_length; i++) {
        if(isspace(source_code[i])) {
            continue;
        }

        if(isalpha(source_code[i])) {
            size_t k = i;

            while(isalpha(source_code[k])) {
                buffer = realloc(buffer, sizeof(char) * (buffer_index + 1));
                buffer[buffer_index] = source_code[k];
                buffer_index++;
                k++;
            }

            token.text = str_clone(buffer);

            if(strcmp(buffer, "return") == 0) {
                token.type = T_KW_RETURN;

                vec_push(tokens, &token);
            } else {
                token.type = T_IDENTIFIER;

                vec_push(tokens, &token);
            }

            memset(buffer, 0, sizeof(char) * (buffer_index + 1));

            buffer_index = 0;
            i = k - 1;

            continue;
        }

        if(isdigit(source_code[i])) {
            size_t j = i;

            while(isdigit(source_code[j])) {
                buffer = realloc(buffer, sizeof(char) * (buffer_index + 1));
                buffer[buffer_index] = source_code[j];
                buffer_index++;
                j++;
            }

            token.type = T_LITERAL;
            token.text = str_clone(buffer);

            vec_push(tokens, &token);
            memset(buffer, 0, sizeof(char) * (buffer_index + 1));

            buffer_index = 0;
            i = j - 1;

            continue;
        }

        token.text = str_clone(&source_code[i]);

        switch(source_code[i]) {
            case '=':
                token.type = T_EQUAL;
                
                vec_push(tokens, &token);
                
                break;
            case ';':
                token.type = T_SEMICOLON;
                
                vec_push(tokens, &token);
                
                break;
            case '(':
                token.type = T_L_ROUND_PARENT;
                
                vec_push(tokens, &token);
                
                break;
            case ')':
                token.type = T_R_ROUND_PARENT;
                
                vec_push(tokens, &token);
                
                break;
            case '+':
                token.type = T_PLUS;
                
                vec_push(tokens, &token);
                
                break;
            case '-':
                token.type = T_MINUS;
                
                vec_push(tokens, &token);
                
                break;
            case '*':
                token.type = T_STAR;
                
                vec_push(tokens, &token);
                
                break;
            case '/':
                token.type = T_SLASH;
                
                vec_push(tokens, &token);
        }
    }

    free(buffer);

    return tokens;
}