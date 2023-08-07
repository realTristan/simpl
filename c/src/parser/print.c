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
 * @return char* The padding
 */
char *build_left_padding(int l_padding)
{
    char *padding = (char *)malloc(sizeof(char) * l_padding);
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
    char *padding = build_left_padding(l_padding);
    printf("%sbin_expr {\n", padding);

    // While there is a left binary expression, print it
    while (bin_expr->left)
    {
        printf("%s  {\n", padding);
        printf("%s    left: {\n", padding);
        printf("%s      type: %d\n", padding, bin_expr->left->right->type);
        printf("%s      value: \"%s\"\n", padding, bin_expr->left->right->value);
        printf("%s    },\n", padding);
        printf("%s    op: \"%s\"\n", padding, bin_expr->op);
        printf("%s    right: {\n", padding);
        printf("%s      type: %d\n", padding, bin_expr->right->type);
        printf("%s      value: \"%s\"\n", padding, bin_expr->right->value);
        printf("%s    }\n", padding);
        printf("%s  },\n", padding);
        bin_expr = bin_expr->left;
    }

    // Print the closing brace
    printf("%s}\n", padding);
}

/**
 * @brief Prints a program.
 *
 * @param program The program.
 */
void print_program(program_t *program)
{
    printf("\nprogram: {\n  type: \"%d\"", program->type);
    printf(",\n  body: [\n");
    for (int i = 0; i < program->body.size; i++)
    {
        // Print the statement
        stmt_t *stmt = program->body.values[i];
        if (stmt->type == NODE_TYPE_REGULAR_EXPRESSION)
        {
            printf("    {\n      stmt_type: %d", stmt->type);
            printf(",\n      expr: {\n        value: \"%s\"\n        type: %d\n      }\n    },\n", stmt->reg_expr->value, stmt->reg_expr->type);
        }
        else if (stmt->type == NODE_TYPE_BINARY_EXPRESSION)
        {
            print_bin_expr(stmt->bin_expr, 4);
            continue;
        }
    }
    printf("  ]\n}\n");
}

#endif // PARSER_PRINT_C