all: output execute

output:
	gcc src/main.c src/utils/utils.c src/lexer/lexer.c -o build/main

execute:
	./build/main