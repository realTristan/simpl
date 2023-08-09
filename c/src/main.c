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
    // Print repl intiialization notification
    printf("\nrepl initialized. now coding in simpl.\n");

    // Create a new token array
    token_array_t *token_array = new_token_array();

    // While the user doesn't want to exit, tokenize the inputted src
    while (1) {
        char src[100];
        printf("\n>> ");
        fgets(src, 100, stdin);

        // Tokenize the source
        tokenize(token_array, src);

        // Print the tokens
        print_token_array(token_array);

        // Parse the tokens
        parse(token_array);
    }
}

#endif // MAIN