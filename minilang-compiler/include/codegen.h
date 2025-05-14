#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm-c/Core.h>
#include "ast.h"

LLVMModuleRef create_module();
LLVMValueRef generate_code(LLVMModuleRef module, ASTNode* node);
void execute_and_print_result(LLVMModuleRef module);
static LLVMValueRef generate_expression_code(LLVMBuilderRef builder, ASTNode* node);

#endif
