#ifndef AST_H
#define AST_H

typedef enum {
    NODE_INT,
    NODE_BINARY_OP
} NodeType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
} BinaryOp;

typedef struct ASTNode {
    NodeType node_type;
    union {
        int int_value;
        struct {
            BinaryOp op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;
    } data;
} ASTNode;

ASTNode* createASTNode(NodeType type);
void freeASTNode(ASTNode* node);

#endif
