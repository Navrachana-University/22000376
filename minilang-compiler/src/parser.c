#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>

Parser* create_parser(Lexer* lexer) {
    if (!lexer) return NULL;
    
    Parser* parser = malloc(sizeof(Parser));
    if (!parser) return NULL;

    parser->lexer = lexer;
    parser->current_token = get_next_token(lexer);
    return parser;
}

void free_parser(Parser* parser) {
    if (parser) {
        if (parser->current_token) free_token(parser->current_token);
        free(parser);
    }
}

void advance(Parser* parser) {
    if (!parser || !parser->current_token) return;
    
    free_token(parser->current_token);
    parser->current_token = get_next_token(parser->lexer);
}

ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_term(parser);
    
    while (parser->current_token->type == TOKEN_PLUS || 
           parser->current_token->type == TOKEN_MINUS) {
        TokenType op = parser->current_token->type;
        advance(parser);
        ASTNode* right = parse_term(parser);
        
        ASTNode* new_node = createASTNode(NODE_BINARY_OP);
        new_node->data.binop.op = (op == TOKEN_PLUS) ? OP_ADD : OP_SUB;
        new_node->data.binop.left = left;
        new_node->data.binop.right = right;
        
        left = new_node;
    }
    
    return left;
}

ASTNode* parse_term(Parser* parser) {
    ASTNode* left = parse_factor(parser);
    
    while (parser->current_token->type == TOKEN_MUL || 
           parser->current_token->type == TOKEN_DIV) {
        TokenType op = parser->current_token->type;
        advance(parser);
        ASTNode* right = parse_factor(parser);
        
        ASTNode* new_node = createASTNode(NODE_BINARY_OP);
        new_node->data.binop.op = (op == TOKEN_MUL) ? OP_MUL : OP_DIV;
        new_node->data.binop.left = left;
        new_node->data.binop.right = right;
        
        left = new_node;
    }
    
    return left;
}

ASTNode* parse_factor(Parser* parser) {
    if (parser->current_token->type == TOKEN_INT) {
        ASTNode* node = createASTNode(NODE_INT);
        node->data.int_value = parser->current_token->value;
        advance(parser);
        return node;
    }
    
    fprintf(stderr, "Unexpected token in factor\n");
    exit(1);
    return NULL;
}
