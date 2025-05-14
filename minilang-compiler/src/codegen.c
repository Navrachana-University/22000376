#include "../include/codegen.h"
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <stdio.h>
#include <stdlib.h>

// TAC generation state
static int temp_counter = 0;

// Helper function for TAC generation
void generate_tac(ASTNode* node) {
    if (!node) return;

    switch (node->node_type) {
        case NODE_INT:
            printf("t%d = %d\n", temp_counter++, node->data.int_value);
            break;
        case NODE_BINARY_OP: {
            generate_tac(node->data.binop.left);
            int left_temp = temp_counter - 1;
            
            generate_tac(node->data.binop.right);
            int right_temp = temp_counter - 1;

            const char* op;
            switch (node->data.binop.op) {
                case OP_ADD: op = "+"; break;
                case OP_SUB: op = "-"; break;
                case OP_MUL: op = "*"; break;
                case OP_DIV: op = "/"; break;
                default: op = "?";
            }
            printf("t%d = t%d %s t%d\n", temp_counter, left_temp, op, right_temp);
            temp_counter++;
            break;
        }
    }
}

static LLVMValueRef generate_expression_code(LLVMBuilderRef builder, ASTNode* node) {
    switch (node->node_type) {
        case NODE_INT:
            return LLVMConstInt(LLVMInt32Type(), node->data.int_value, 0);
        case NODE_BINARY_OP: {
            LLVMValueRef left = generate_expression_code(builder, node->data.binop.left);
            LLVMValueRef right = generate_expression_code(builder, node->data.binop.right);
            switch (node->data.binop.op) {
                case OP_ADD: return LLVMBuildAdd(builder, left, right, "addtmp");
                case OP_SUB: return LLVMBuildSub(builder, left, right, "subtmp");
                case OP_MUL: return LLVMBuildMul(builder, left, right, "multmp");
                case OP_DIV: return LLVMBuildSDiv(builder, left, right, "divtmp");
                default: return NULL;
            }
        }
        default: return NULL;
    }
}

LLVMModuleRef create_module() {
    return LLVMModuleCreateWithName("minilang_module");
}

LLVMValueRef generate_code(LLVMModuleRef module, ASTNode* node) {
    // Reset TAC counter for each new code generation
    temp_counter = 0;
    
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMTypeRef param_types[] = {};
    LLVMTypeRef func_type = LLVMFunctionType(LLVMInt32Type(), param_types, 0, 0);
    LLVMValueRef main_func = LLVMAddFunction(module, "main", func_type);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    LLVMValueRef result = generate_expression_code(builder, node);
    LLVMBuildRet(builder, result);
    LLVMDisposeBuilder(builder);
    return main_func;
}

void execute_and_print_result(LLVMModuleRef module) {
    LLVMLinkInMCJIT();
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    
    char* error = NULL;
    LLVMExecutionEngineRef engine;
    
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error)) {
        fprintf(stderr, "JIT Error: %s\n", error);
        LLVMDisposeMessage(error);
        exit(1);
    }

    LLVMValueRef main_fn = LLVMGetNamedFunction(module, "main");
    if (!main_fn) {
        fprintf(stderr, "Main function not found\n");
        exit(1);
    }

    LLVMGenericValueRef result = LLVMRunFunction(engine, main_fn, 0, NULL);
    printf("%d\n", (int)LLVMGenericValueToInt(result, 1));
    
    LLVMDisposeExecutionEngine(engine);
}void generate_tac(ASTNode* node) {
    static int temp_count = 0;
    if (!node) return;
    
    switch(node->node_type) {
        case NODE_INT:
            printf("t%d = %d\n", temp_count++, node->data.int_value);
            break;
        case NODE_VARIABLE:
            printf("t%d = %s\n", temp_count++, node->data.var_name);
            break;
        case NODE_BINARY_OP: {
            generate_tac(node->data.binop.left);
            int left = temp_count-1;
            generate_tac(node->data.binop.right);
            int right = temp_count-1;
            const char* op = "";
            switch(node->data.binop.op) {
                case OP_ADD: op = "+"; break;
                case OP_SUB: op = "-"; break;
                case OP_MUL: op = "*"; break;
                case OP_DIV: op = "/"; break;
            }
            printf("t%d = t%d %s t%d\n", temp_count, left, op, right);
            temp_count++;
            break;
        }
    }
}
