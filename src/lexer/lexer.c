#ifndef LEXER_C
#define LEXER_C

#include "../utils/utils.h"
#include "token.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define f f_real_name
/**
 * @brief Pushes a token to the back of a token array.
 *
 * @param tokens The token array.
 * @param token The token to push.
 * @param token_count The amount of tokens.
 */
Token *push_back_token(Token *tokens, Token token, int *token_count)
{
    // Create a new array of tokens with +1 length
    Token *new_tokens = malloc(sizeof(Token) * (*token_count + 1));
    // Copy the old tokens to the new tokens
    for (int i = 0; i < *token_count; i++)
    {
        new_tokens[i] = tokens[i];
    }

    // Add the new token to the end of the new tokens
    new_tokens[*token_count] = token;

    // Update the token count
    *token_count += 1;

    // Free the old tokens
    free(tokens);

    // Return the new tokens
    return new_tokens;
}
#undef f

/**
 * @brief Tokenizes a string.
 *
 * @param src The string to tokenize.
 * @return const Token* The tokens.
 */
Token *tokenize(char *src, int *token_count)
{
    // Split the src
    int split_count = 0;
    int split_tokens_index = 0;

    // Split the src by spaces
    char **split_tokens = split_str(src, ' ', &split_count);

    // The list of tokens
    Token *tokens = malloc(sizeof(Token) * split_count);

    // Build each token
    while (split_tokens_index < split_count)
    {
        // Pop the token
        char *token = split_tokens[split_tokens_index];
        split_tokens_index++;

        // Check the token type
        switch (token[0])
        {
        case ' ':
        case '\n':
        case '\t':
            continue;
        case TOKEN_TYPE_LEFT_PAREN_VALUE:
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_LEFT_PAREN, "("}, token_count);
            break;
        case ')':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_RIGHT_PAREN, ")"}, token_count);
            break;
        case '=':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_EQUAL, "="}, token_count);
            break;
        case '+':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_PLUS, "+"}, token_count);
            break;
        case '-':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_MINUS, "-"}, token_count);
            break;
        case '*':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_MULTIPLY, "*"}, token_count);
            break;
        case '/':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_DIVIDE, "/"}, token_count);
            break;
        default:
            printf("Unknown Token: [%s]\n", token);
            break;
        }
    }

    // Free the split tokens
    free(split_tokens);

    // Return the tokens
    return tokens;
}

#endif // LEXER_C