#include "../include/ast.h"
#include <stdlib.h>

ASTNode* createASTNode(NodeType type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->node_type = type;
    return node;
}

void freeASTNode(ASTNode* node) {
    if (node) {
        if (node->node_type == NODE_BINARY_OP) {
            freeASTNode(node->data.binop.left);
            freeASTNode(node->data.binop.right);
        }
        free(node);
    }
}
