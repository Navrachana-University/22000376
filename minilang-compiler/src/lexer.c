#include "../include/lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Lexer* create_lexer(const char* input) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->input = strdup(input);
    lexer->position = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current_char = lexer->input[0];
    return lexer;
}

void free_lexer(Lexer* lexer) {
    free((void*)lexer->input);
    free(lexer);
}

static void advance_lexer(Lexer* lexer) {
    if (lexer->current_char == '\n') {
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }
    lexer->position++;
    lexer->current_char = lexer->position < strlen(lexer->input) ? 
                         lexer->input[lexer->position] : '\0';
}

Token* get_next_token(Lexer* lexer) {
    while (isspace(lexer->current_char)) {
        advance_lexer(lexer);
    }

    if (lexer->current_char == '\0') {
        return create_token(TOKEN_EOF, 0, lexer->line, lexer->column);
    }

    if (isdigit(lexer->current_char)) {
        int start_column = lexer->column;
        char num_str[32];
        int i = 0;
        while (isdigit(lexer->current_char)) {
            num_str[i++] = lexer->current_char;
            advance_lexer(lexer);
        }
        num_str[i] = '\0';
        return create_token(TOKEN_INT, atoi(num_str), lexer->line, start_column);
    }

    if (isalpha(lexer->current_char)) {
        int start_column = lexer->column;
        char var_name[32];
        int i = 0;
        while (isalpha(lexer->current_char)) {
            var_name[i++] = lexer->current_char;
            advance_lexer(lexer);
        }
        var_name[i] = '\0';
        return create_token(TOKEN_IDENTIFIER, 0, lexer->line, start_column);
    }

    if (lexer->current_char == '=') {
        advance_lexer(lexer);
        return create_token(TOKEN_EQ, 0, lexer->line, lexer->column-1);
    }

    // ... (rest of your token handling)
}
