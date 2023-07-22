all: output execute

output:
	gcc src/main.c src/utils/ints.c src/utils/strings.c src/lexer/lexer.c -o build/main

execute:
	./build/main