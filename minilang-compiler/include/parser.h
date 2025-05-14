#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer* lexer;
    Token* current_token;
} Parser;

// Public interface
Parser* create_parser(Lexer* lexer);
void free_parser(Parser* parser);
ASTNode* parse_expression(Parser* parser);

// Internal functions
void advance(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_factor(Parser* parser);

#endif
