#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include <stdlib.h>

/**
 * @brief Parses tokens.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 */
void parser(Token *tokens, size_t tokens_size);

#endif // PARSER_H