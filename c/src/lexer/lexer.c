#ifndef LEXER_C
#define LEXER_C

#include "../utils/utils.h"
#include "../tokens/token.h"
#include "../tokens/token_array.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Tokenizes a string.
 *
 * @param tokens The tokens array.
 * @param src The string to tokenize.
 * @return void
 */
void tokenize(token_array_t *tokens, char *src)
{
    // Split the src
    split_array_t split_tokens = split_str(src, ' ');

    // Build each token
    for (int i = 0; i < split_tokens.size; i++)
    {
        // Pop the token
        char *token_str = split_tokens.values[i];

        // Check the token type
        switch (token_str[0])
        {
        case ' ':
        case '\n':
        case '\t':
            continue;
        case TOKEN_TYPE_LEFT_PAREN_VALUE:
            push_back_token(tokens, new_token(TOKEN_TYPE_LEFT_PAREN, token_str));
            break;
        case TOKEN_TYPE_RIGHT_PAREN_VALUE:
            push_back_token(tokens, new_token(TOKEN_TYPE_RIGHT_PAREN, token_str));
            break;
        case TOKEN_TYPE_ASSIGN_VALUE:
            push_back_token(tokens, new_token(TOKEN_TYPE_ASSIGN, token_str));
            break;
        case TOKEN_TYPE_PLUS_VALUE:
            push_back_token(tokens, new_token(TOKEN_TYPE_PLUS, token_str));
            break;
        case TOKEN_TYPE_MINUS_VALUE:
            push_back_token(tokens, new_token(TOKEN_TYPE_MINUS, token_str));
            break;
        case TOKEN_TYPE_MULTIPLY_VALUE:
            push_back_token(tokens, new_token(TOKEN_TYPE_MULTIPLY, token_str));
            break;
        case TOKEN_TYPE_DIVIDE_VALUE:
            push_back_token(tokens, new_token(TOKEN_TYPE_DIVIDE, token_str));
            break;
        default:
            if (is_int(token_str))
            {
                push_back_token(tokens, new_token(TOKEN_TYPE_NUMBER, token_str));
            }
            else if (is_alpha(token_str))
            {
                if (strcmp(token_str, TOKEN_TYPE_LET_VALUE) == 0)
                {
                    push_back_token(tokens, new_token(TOKEN_TYPE_LET, token_str));
                }
                else if (strcmp(token_str, TOKEN_TYPE_NULL_VALUE) == 0)
                {
                    push_back_token(tokens, new_token(TOKEN_TYPE_NULL, token_str));
                }
                else
                {
                    push_back_token(tokens, new_token(TOKEN_TYPE_IDENTIFIER, token_str));
                }
            }
            else
            {
                printf("Unknown token: [%s]\n", token_str);
                exit(1);
            }
            break;
        }
    }

    // Push back the final EOF token.
    push_back_token(tokens, new_token(TOKEN_TYPE_EOF, "EOF"));
}

#endif // LEXER_C
