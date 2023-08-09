#ifndef TOKEN_C
#define TOKEN_C

#include "token.h"
#include <stdlib.h>

/**
 * @brief Makes a token.
 *
 * @param type The token type.
 * @param value The token value.
 * @return token_t The token.
 */
token_t new_token(token_type type, char *value)
{
    return (token_t){type, value};
}
token_t new_token_char(token_type type, char value)
{
    char *str = malloc(sizeof(char) * 2);
    str[0] = value;
    str[1] = '\0';
    return (token_t){type, str};
}

#endif // TOKEN_C