#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stdlib.h>

/**
 * @brief Tokenizes a string.
 *
 * @param src The string to tokenize.
 * @param token_size The amount of tokens.
 * @return const Token* The tokens.
 */
Token **tokenize(char *src, size_t *token_size);

#endif // LEXER_H