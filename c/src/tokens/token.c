#ifndef TOKEN_C
#define TOKEN_C

#include "token.h"

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

#endif // TOKEN_C