#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    const char* input;
    int position;
    int line;
    int column;
    char current_char;
} Lexer;

Lexer* create_lexer(const char* input);
void free_lexer(Lexer* lexer);
Token* get_next_token(Lexer* lexer);  // Make sure this is declared

#endif
