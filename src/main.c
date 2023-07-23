#ifndef MAIN
#define MAIN

#include <stdio.h>

#include "lexer/lexer.h"

int main(void)
{
    // The source code
    char *src = "let x = 45 ";

    // Tokenize the source
    int token_count = 0;
    Token *tokens = tokenize(src, &token_count);

    // Print the tokens
    for (int i = 0; i < token_count; i++)
    {
        printf("Token (%d): [%s]\n", tokens[i].type, tokens[i].value);
    }
}

#endif // MAIN