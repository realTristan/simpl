#ifndef PARSER_UTILS_C
#define PARSER_UTILS_C

#include "../nodes/nodes.h"

#include <stdio.h>

/** TODO
 *
 * - Fix the print_bin_expr_2 function
 *
 * - Add more testing functions
 *
 *
 *
 *
 *
 *
 *
 */

#define f print_bin_expr_2
/**
 * @brief Prints a binary expression.
 *
 * @param bin_expr The binary expression.
 * @param span The span.
 * @return void
 */
void print_bin_expr_2(BinaryExpr *bin_expr, char *span)
{
    printf("%sBinaryExpr {\n", span);
    printf("%s  type: %d\n", span, bin_expr->type);
    printf("%s  left: {\n", span);
    printf("%s    type: %d\n", span, bin_expr->left->type);
    printf("%s    left: {\n", span);
    printf("%s      type: %d\n", span, bin_expr->left->left->type);
    printf("%s      value: \"%s\"\n", span, bin_expr->left->right->value);
    printf("%s    }\n", span);
    printf("%s    right: {\n", span);
    printf("%s      type: %d\n", span, bin_expr->left->right->type);
    printf("%s      value: \"%s\"\n", span, bin_expr->left->right->value);
    printf("%s    }\n", span);
    printf("%s    op: \"%s\"\n", span, bin_expr->left->op);
    printf("%s  }\n", span);
    printf("%s  right: {\n", span);
    printf("%s    type: %d\n", span, bin_expr->right->type);
    printf("%s    value: \"%s\"\n", span, bin_expr->right->value);
    printf("%s  }\n", span);
    printf("%s  op: \"%s\"\n", span, bin_expr->op);
    printf("%s}\n", span);
}
#undef f

#define f print_bin_expr
/**
 * @brief Prints a binary expression.
 *
 * @param bin_expr The binary expression.
 * @return void
 */
void print_bin_expr(BinaryExpr *bin_expr)
{
    printf("\n    {\n      type: %d\n      left: {\n        type: \"%d\",\n        value: \"%s\"\n      },\n", bin_expr->type, bin_expr->left->right->type, bin_expr->left->right->value);
    printf("      right: {\n        type: \"%d\",\n        value: \"%s\"\n      },\n", bin_expr->right->type, bin_expr->right->value);
    printf("      op: \"%s\"\n    }", bin_expr->op);
}

/**
 * @brief Prints a program.
 *
 * @param program The program.
 */
void print_program(Program *program)
{
    printf("{\n  type: \"%d\"", program->type);
    printf(",\n  body: [\n");
    for (int i = 0; i < program->body_size; i++)
    {
        if (program->body[i]->expr != NULL)
            printf("\n    {\n      type: %d\n      value: \"%s\"\n    }", program->body[i]->expr->type, program->body[i]->expr->value);

        if (program->body[i]->bin_expr != NULL)
            print_bin_expr(program->body[i]->bin_expr);
            // print_bin_expr_2(program->body[i]->bin_expr, "    ");

        // Print a comma if not the last element
        if (i != program->body_size - 1)
        {
            printf(",");
        }
    }
    printf("\n  ]\n}\n");
}

#endif // PARSER_UTILS_C