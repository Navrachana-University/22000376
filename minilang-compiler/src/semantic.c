#include "semantic.h"
#include "program.h"
#include "ast.h"
#include <stdio.h>

int analyze(Program* program) {
    if (!program || !program->root) {
        fprintf(stderr, "Error: Empty program\n");
        return 0;
    }
    
    // Basic semantic check - verify the AST is valid
    // Add your specific semantic rules here
    return 1; // Return 1 for success
}
