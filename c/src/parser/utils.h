#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "../nodes/node_structs.h"

/**
 * @brief Prints a binary expression.
 *
 * @param bin_expr The binary expression.
 * @param lPadding The left padding.
 * @return void
 */
void print_bin_expr(BinaryExpr *bin_expr, int lPadding);

/**
 * @brief Prints a program.
 *
 * @param program The program.
 */
void print_program(Program *program);

#endif // PARSER_UTILS_H