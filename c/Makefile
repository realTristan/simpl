all: output execute

files = src/main.c src/utils/utils.c src/lexer/lexer.c src/parser/parser.c src/nodes/nodes.c  src/parser/utils.c

output:
	gcc $(files) -o build/main

execute:
	./build/main