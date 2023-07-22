#include <stdio.h>

#include "lexer/lexer.h"
#include "common/types.h"

int main(void)
{
    string src = "let x = 5";
    Token *tokens = tokenize(src);
    for (int i = 0; i < sizeof(tokens); i++)
    {
        printf("Token: %s\n", tokens[i].value);
    }
}