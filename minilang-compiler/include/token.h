#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_EOF,
    TOKEN_INT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_IDENTIFIER,
    TOKEN_EQ
} TokenType;

typedef struct {
    TokenType type;
    int value;
    int line;
    int column;
} Token;

Token* create_token(TokenType type, int value, int line, int column);
void free_token(Token* token);

#endif
