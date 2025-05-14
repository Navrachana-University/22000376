#include <stdlib.h>
#include "program.h"

Program* createProgram(ASTNode* root) {
    Program* program = malloc(sizeof(Program));
    if (program) {
        program->root = root;
        program->error_count = 0;
    }
    return program;
}

void freeProgram(Program* program) {
    if (program) {
        if (program->root) {
            freeASTNode(program->root);  // Ensure this exists in ast.c
        }
        free(program);
    }
}
