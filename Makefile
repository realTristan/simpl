all: output execute

output:
	gcc src/main.c src/utils/utils.c src/lexer/lexer.c src/parser/parser.c -o build/main

execute:
	./build/main