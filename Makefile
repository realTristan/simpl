all: output execute

output:
	gcc src/main.c -o build/main

execute:
	./build/main