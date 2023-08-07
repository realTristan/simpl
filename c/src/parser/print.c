#ifndef PARSER_PRINT_C
#define PARSER_PRINT_C

#include "../nodes/node_types.h"
#include "../nodes/nodes.h"

#include <stdio.h>

#define f build_left_padding
/**
 * @brief Builds the padding
 * 
 * @param l_padding The left padding
 * 
 */
char* build_left_padding(int l_padding)
{
    char* padding = (char*)malloc(sizeof(char) * l_padding);
    for (int i = 0; i < l_padding; i++)
    {
        padding[i] = ' ';
    }
    padding[l_padding] = '\0';
    return padding;
}
#undef f

/**
 * @brief Prints a binary expression.
 *
 * @param bin_expr The binary expression.
 * @param l_padding The left padding.
 * @return void
 */
void print_bin_expr(bin_expr_t *bin_expr, int l_padding)
{
    
}

/**
 * @brief Prints a program.
 *
 * @param program The program.
 */
void print_program(program_t *program)
{
    
}

#endif // PARSER_PRINT_C