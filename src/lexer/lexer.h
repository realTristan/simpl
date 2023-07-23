#ifndef LEXER_H
#define LEXER_H

#include "../common/types.h"
#include "token.h"

/**
 * @brief Tokenizes a string.
 *
 * @param src The string to tokenize.
 * @param token_count The amount of tokens.
 * @return const Token* The tokens.
 */
Token *tokenize(string src, int *token_count);

#endif // LEXER_H