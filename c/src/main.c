#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "tokens/token_array.h"

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
    char *src = "x + 7";
    // Segmentation fault from above is caused by the print function

    // Create a new token array
    token_array_t *token_array = new_token_array();

    // Tokenize the source
    tokenize(token_array, src);

    // Print the tokens
    print_token_array(token_array);

    // Parse the tokens
    parse(token_array);
}

#endif // MAIN