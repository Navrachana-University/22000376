#include "../include/token.h"
#include <stdlib.h>

Token* create_token(TokenType type, int value, int line, int column) {
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    token->line = line;
    token->column = column;
    return token;
}

void free_token(Token* token) {
    free(token);
}
