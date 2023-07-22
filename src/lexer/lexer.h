#ifndef LEXER_H
#define LEXER_H

#include "token/token.h"
#include "../common/types.h"

/**
 * @brief Tokenizes a string.
 *
 * @param src The string to tokenize.
 * @return const Token* The tokens.
 */
Token *tokenize(string src);

#endif // LEXER_H