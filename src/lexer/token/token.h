#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"
#include "../../common/types.h"

/**
 * @brief A token is a pair of a token type and a value.
 * 
 * @param type The type of the token.
 * @param value The value of the token.
 */
typedef struct Token
{
    TokenType type;
    string value;
} Token;

#endif // TOKEN_H