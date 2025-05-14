#include "lexer.h"
#include <stdio.h>

int main() {
    const char* source = "42";
    Lexer* lexer = createLexer(source);
    Token* token = getNextToken(lexer);
    
    printf("Token type: %d\n", token->type);
    printf("Token value: %d\n", token->value);
    
    destroyLexer(lexer);
    return 0;
}
