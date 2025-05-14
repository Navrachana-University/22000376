#include "../include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        exit(1);
    }

    size_t read = fread(buffer, 1, length, file);
    if (read != length) {
        free(buffer);
        perror("Error reading file");
        exit(1);
    }
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

char* read_stdin() {
    char buffer[1024];
    size_t len = 0;
    char* source = malloc(1024);
    if (!source) {
        perror("Memory allocation failed");
        exit(1);
    }
    source[0] = '\0';

    while (fgets(buffer, sizeof(buffer), stdin)) {
        size_t buf_len = strlen(buffer);
        char* new_source = realloc(source, len + buf_len + 1);
        if (!new_source) {
            free(source);
            perror("Memory reallocation failed");
            exit(1);
        }
        source = new_source;
        strcpy(source + len, buffer);
        len += buf_len;
    }
    return source;
}

int main(int argc, char** argv) {
    bool use_tac = false;
    char* source = NULL;
    char* filename = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--tac") == 0) {
            use_tac = true;
        } else if (strcmp(argv[i], "-") == 0) {
            filename = "-";
        } else {
            filename = argv[i];
        }
    }

    // Handle no arguments case
    if (argc == 1) {
        fprintf(stderr, "Usage: %s [--tac] <filename|->\n", argv[0]);
        return 1;
    }

    // Read input
    if (filename && strcmp(filename, "-") == 0) {
        source = read_stdin();
    } else if (filename) {
        source = read_file(filename);
    } else {
        fprintf(stderr, "Usage: %s [--tac] <filename|->\n", argv[0]);
        return 1;
    }

    // Compilation pipeline
    Lexer* lexer = create_lexer(source);
    Parser* parser = create_parser(lexer);
    ASTNode* ast = parse_expression(parser);
    LLVMModuleRef module = create_module();
    generate_code(module, ast);

    // Optional TAC output
    if (use_tac) {
        printf("=== Three-Address Code ===\n");
        generate_tac(ast);
    }

    printf("=== Three-Address Code ===\n"); 
    generate_tac(ast); 
    execute_and_print_result(module);

    // Cleanup in reverse order of creation
    if (module) LLVMDisposeModule(module);
    if (ast) freeASTNode(ast);
    if (parser) free_parser(parser);
    if (lexer) free_lexer(lexer);
    if (source) free(source);

    return 0;
}