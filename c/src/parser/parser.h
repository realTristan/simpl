#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include <stdlib.h>

/**
 * @brief Parses tokens.
 *
 * @param token_array The tokens array.
 */
void parser(token_array_t *token_array);

#endif // PARSER_H