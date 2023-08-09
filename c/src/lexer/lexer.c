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
    // split_array_t split_tokens = split_str(src, ' ');

    // Get the length of the src
    const size_t srclen = strlen(src);

    // Build each token
    for (unsigned int i = 0; i < srclen; i++)
    {
        // Check the token type
        switch (src[i])
        {
        case ' ':
        case '\n':
        case '\t':
            continue;
        case '(':
            push_back_token(tokens, new_token_char(TOKEN_TYPE_LEFT_PAREN, '('));
            break;
        case ')':
            push_back_token(tokens, new_token_char(TOKEN_TYPE_RIGHT_PAREN, ')'));
            break;
        case '=':
            push_back_token(tokens, new_token_char(TOKEN_TYPE_ASSIGN, '='));
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            push_back_token(tokens, new_token_char(TOKEN_TYPE_BINARY_OPERATOR, src[i]));
            break;
        default:
        {
            if (is_alpha_char(src[i]))
            {
                // Get the identifier
                char *str = malloc(sizeof(char *) * 100); //(srclen - i + 1));
                int index = 0;
                while (i < srclen && is_alpha_char(src[i]) && !is_whitespace(src[i]))
                {
                    str[index] = src[i];
                    index++;
                    i++;
                }
                i--;

                // Convert the str to it's actual size
                char *tmp = malloc(sizeof(char) * (index + 1));
                for (unsigned int j = 0; j < index; j++)
                {
                    tmp[j] = str[j];
                }
                tmp[index] = '\0';

                // Push back the identifier
                if (strcmp(tmp, "let") == 0)
                {
                    push_back_token(tokens, new_token(TOKEN_TYPE_LET, tmp));
                }
                else if (strcmp(tmp, "null") == 0)
                {
                    push_back_token(tokens, new_token(TOKEN_TYPE_NULL, tmp));
                }
                else
                {
                    push_back_token(tokens, new_token(TOKEN_TYPE_IDENTIFIER, tmp));
                }
            }
            else if (is_int_char(src[i]))
            {
                // Get the number
                char *num = malloc(sizeof(char *) * 100); //(srclen - i + 1));
                int index = 0;
                while (i < srclen && is_int_char(src[i]) && !is_whitespace(src[i]))
                {
                    num[index] = src[i];
                    index++;
                    i++;
                }
                i--;

                // Convert the number to it's actual size
                char *tmp = malloc(sizeof(char) * (index + 1));
                for (unsigned int j = 0; j < index; j++)
                {
                    tmp[j] = num[j];
                }
                tmp[index] = '\0';

                // Push back the number
                push_back_token(tokens, new_token(TOKEN_TYPE_NUMBER, tmp));
            }

            else
            {
                printf("Unknown token: [%c]\n", src[i]);
                exit(1);
            }
            break;
        }
        }
    }

    // Push back the final EOF token.
    push_back_token(tokens, new_token(TOKEN_TYPE_EOF, "EOF"));
}

#endif // LEXER_C
