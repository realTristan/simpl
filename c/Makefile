all: output execute

files = src/main.c src/lexer/lexer.c src/nodes/nodes.c src/parser/parser.c src/parser/print.c src/tokens/token_array.c src/tokens/token.c src/utils/utils.c

output:
	gcc $(files) -o build/main

execute:
	./build/main