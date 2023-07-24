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
Token **push_back_token(Token **tokens, Token *token, size_t *tokens_size)
{
    // Create a new array of tokens with +1 length
    Token **new_tokens = malloc(sizeof(Token) * (*tokens_size + 1));
    // Copy the old tokens to the new tokens
    for (int i = 0; i < *tokens_size; i++)
    {
        new_tokens[i] = malloc(sizeof(Token));
        new_tokens[i]->type = tokens[i]->type;
        new_tokens[i]->value = tokens[i]->value;
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

#define f make_token
/**
 * @brief Makes a token.
 *
 * @param type The token type.
 * @param value The token value.
 * @return Token The token.
 */
Token *make_token(TokenType type, char *value)
{
    // Create the token
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;

    // Return the token
    return token;
}

/**
 * @brief Tokenizes a string.
 *
 * @param src The string to tokenize.
 * @return const Token* The tokens.
 */
Token **tokenize(char *src, size_t *tokens_size)
{
    // Split the src
    size_t split_size = 0;
    int split_tokens_index = 0;

    // Split the src by spaces
    char **split_tokens = split_str(src, ' ', &split_size);

    // The list of tokens
    Token **tokens = malloc(sizeof(Token) * split_size);

    // Build each token
    while (split_tokens_index < split_size)
    {
        // Pop the token
        char *token_str = split_tokens[split_tokens_index];
        split_tokens_index++;

        // Token
        Token *token = malloc(sizeof(Token));

        // Check the token type
        switch (token_str[0])
        {
        case ' ':
        case '\n':
        case '\t':
            continue;
        case TOKEN_TYPE_LEFT_PAREN_VALUE:
            token = make_token(TOKEN_TYPE_LEFT_PAREN, "(");
            break;
        case TOKEN_TYPE_RIGHT_PAREN_VALUE:
            token = make_token(TOKEN_TYPE_RIGHT_PAREN, ")");
            break;
        case TOKEN_TYPE_ASSIGN_VALUE:
            token = make_token(TOKEN_TYPE_ASSIGN, "=");
            break;
        case TOKEN_TYPE_PLUS_VALUE:
            token = make_token(TOKEN_TYPE_PLUS, "+");
            break;
        case TOKEN_TYPE_MINUS_VALUE:
            token = make_token(TOKEN_TYPE_MINUS, "-");
            break;
        case TOKEN_TYPE_MULTIPLY_VALUE:
            token = make_token(TOKEN_TYPE_MULTIPLY, "*");
            break;
        case TOKEN_TYPE_DIVIDE_VALUE:
            token = make_token(TOKEN_TYPE_DIVIDE, "/");
            break;
        default:
            if (is_int(token_str))
            {
                token = make_token(TOKEN_TYPE_NUMBER, token_str);
            }
            else if (is_alpha(token_str))
            {
                if (strcmp(token_str, TOKEN_KEYWORD_LET) == 0)
                {
                    token = make_token(TOKEN_TYPE_LET, TOKEN_KEYWORD_LET);
                }
                else
                {
                    token = make_token(TOKEN_TYPE_IDENTIFIER, token_str);
                }
            }
            else
            {
                printf("Unknown token: [%s]\n", token_str);
                exit(1);
            }
            break;
        }

        // Push back the token
        tokens = push_back_token(tokens, token, tokens_size);
    }

    // Free the split tokens
    free(split_tokens);

    // Pushback the EOF token
    Token *eof_token = make_token(TOKEN_TYPE_EOF, "EOF");
    tokens = push_back_token(tokens, eof_token, tokens_size);

    // Return the tokens
    return tokens;
}

#endif // LEXER_C