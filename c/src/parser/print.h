#ifndef PARSER_PRINT_H
#define PARSER_PRINT_H

#include "../nodes/node_types.h"
#include "../nodes/nodes.h"

#include <stdio.h>

/**
 * @brief Prints a binary expression.
 *
 * @param bin_expr The binary expression.
 * @param l_padding The left padding.
 * @return void
 */
void print_bin_expr(bin_expr_t *bin_expr, int l_padding);

/**
 * @brief Prints a program.
 *
 * @param program The program.
 */
void print_program(program_t *program);

#endif // PARSER_PRINT_H