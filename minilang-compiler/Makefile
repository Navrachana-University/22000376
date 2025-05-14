CC = clang
CFLAGS = -g -Iinclude -I/opt/homebrew/opt/llvm/include -std=c11
LDFLAGS = -L/opt/homebrew/opt/llvm/lib -lLLVM -lLLVMOrcJIT -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMAnalysis -lLLVMCore -lLLVMSupport

SRC = src/main.c src/lexer.c src/parser.c src/ast.c src/codegen.c src/semantic.c src/program.c src/token.c
OBJ = $(SRC:.c=.o)

minilang: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) minilang output.ll output
