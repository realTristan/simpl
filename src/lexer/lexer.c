#ifndef LEXER_C
#define LEXER_C

#include "../utils/utils.h"
#include "token.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define f push_back_token
/**
 * @brief Pushes a token to the back of a token array.
 *
 * @param tokens The token array.
 * @param token The token to push.
 * @param tokens_size The amount of tokens.
 */
Token *push_back_token(Token *tokens, Token token, size_t *tokens_size)
{
    // Create a new array of tokens with +1 length
    Token *new_tokens = malloc(sizeof(Token) * (*tokens_size + 1));
    // Copy the old tokens to the new tokens
    for (int i = 0; i < *tokens_size; i++)
    {
        new_tokens[i] = tokens[i];
    }

    // Add the new token to the end of the new tokens
    new_tokens[*tokens_size] = token;

    // Update the token size
    *tokens_size += 1;

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
Token *tokenize(char *src, size_t *tokens_size)
{
    // Split the src
    size_t split_size = 0;
    int split_tokens_index = 0;

    // Split the src by spaces
    char **split_tokens = split_str(src, ' ', &split_size);

    // The list of tokens
    Token *tokens = malloc(sizeof(Token) * split_size);

    // Build each token
    while (split_tokens_index < split_size)
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
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_LEFT_PAREN, "("}, tokens_size);
            break;
        case ')':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_RIGHT_PAREN, ")"}, tokens_size);
            break;
        case '=':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_EQUAL, "="}, tokens_size);
            break;
        case '+':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_PLUS, "+"}, tokens_size);
            break;
        case '-':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_MINUS, "-"}, tokens_size);
            break;
        case '*':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_MULTIPLY, "*"}, tokens_size);
            break;
        case '/':
            tokens = push_back_token(tokens, (Token){TOKEN_TYPE_DIVIDE, "/"}, tokens_size);
        default:
            if (is_int(token))
            {
                tokens = push_back_token(tokens, (Token){TOKEN_TYPE_NUMBER, token}, tokens_size);
            }
            else if (is_alpha(token))
            {
                if (strcmp(token, TOKEN_KEYWORD_LET) == 0)
                {
                    tokens = push_back_token(tokens, (Token){TOKEN_TYPE_LET, token}, tokens_size);
                }
            }
            else
            {
                printf("Unknown token: [%s]\n", token);
                exit(1);
            }
            break;
        }
    }

    // Free the split tokens
    free(split_tokens);

    // Return the tokens
    return push_back_token(
        tokens, (Token){TOKEN_TYPE_EOF, "EOF"}, tokens_size);
}

#endif // LEXER_C