#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast.h"

typedef struct Program {
    ASTNode* root;       // The root AST node (previously called 'expr' in semantic.c)
    int error_count;     // Number of semantic errors
    // Add other necessary fields
} Program;

// Constructor that takes an AST root node
Program* createProgram(ASTNode* root);

// Destructor
void freeProgram(Program* program);

#endif
