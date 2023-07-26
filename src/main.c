#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "parser/parser.h"

/** Notes
 * 
 * If the interpreter doesn't work, take a look at the parenthesis handling.
 * Everything was working fine before that. Also, FIND A BETTER WAY TO PRINT
 * the AST!!
 * 
 * Currently, when printing, the bottom binary expressions are the first, and the top
 * binary expressions are the last. Also, very confusing, but, the regular expressions
 * are in sequential order. This is why we need a better way to print the AST...
 * 
 */
int main(void)
{
    // The source code
    // char *src = "let x = 45 * ( 10 - 2 )";
    char *src = "( 10 + 2 ) - ( 1 + 4 )";

    // Tokenize the source
    size_t tokens_size = 0;
    Token **tokens = tokenize(src, &tokens_size);

    // Print the tokens
    for (int i = 0; i < tokens_size; i++)
    {
        printf("Token (%d): [%s]\n", tokens[i]->type, tokens[i]->value);
    }

    // Parse the tokens
    parser(tokens, tokens_size);
}

#endif // MAIN