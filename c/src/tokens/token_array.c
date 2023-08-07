#ifndef TOKEN_ARRAY_H
#define TOKEN_ARRAY_H

#include "token.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief A dynamic array of tokens.
 *
 */
typedef struct token_array_t
{
    token_t *tokens;
    int size;
} token_array_t;

/**
 * @brief Pushes a token to the back of a token array.
 *
 * @param tokens The token array.
 * @param token The token to push.
 * @param tokens_size The amount of tokens.
 * @return void
 */
void push_back_token(token_array_t *tokens, token_t token)
{
    // Add the new token to the end of the new tokens
    tokens->tokens[tokens->size] = token;

    // Update the token size
    tokens->size++;
}

/**
 * @brief Makes a token array.
 *
 * @return token_tArray The token array.
 */
token_array_t *new_token_array()
{
    // Create the token array
    token_array_t *token_array = malloc(sizeof(token_array_t));
    token_array->size = 0;
    token_array->tokens = malloc(sizeof(token_t));

    // Return the token array
    return token_array;
}

/**
 * @brief Prints a token array.
 *
 * @param token_array The token array.
 * @return void
 */
void print_token_array(token_array_t *token_array)
{
    // Print the tokens
    for (int i = 0; i < token_array->size; i++)
    {
        printf("Token (%d): [%s]\n", token_array->tokens[i].type, token_array->tokens[i].value);
    }
}

/**
 * @brief Frees a token array.
 *
 * @param token_array The token array.
 * @return void
 */
void free_token_array(token_array_t *token_array)
{
    // Free the tokens
    for (int i = 0; i < token_array->size; i++)
    {
        free(token_array->tokens[i].value);
    }

    // Free the token array
    free(token_array);
}

#endif // TOKEN_ARRAY_H