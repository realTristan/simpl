#ifndef PARSER_UTILS_C
#define PARSER_UTILS_C

#include "../nodes/nodes.h"

#include <stdio.h>

/**
 * @brief Prints a program.
 *
 * @param program The program.
 */
void print_program(Program *program)
{
    printf("{\n  type: \"%d\"", program->type);
    printf(",\n  body: [");
    for (int i = 0; i < program->body_size; i++)
    {
        if (program->body[i]->expr != NULL)
        {
            printf("\n    {\n      type: %d\n      value: \"%s\"\n    }", program->body[i]->expr->type, program->body[i]->expr->value);
        }

        if (program->body[i]->bin_expr != NULL)
        {
            BinaryExpr *bin_expr = program->body[i]->bin_expr;
            printf("\n    {\n      type: %d\n      left: {\n        type: \"%d\",\n        value: \"%s\"\n      },\n", bin_expr->type, bin_expr->left->right->type, bin_expr->left->right->value);
            printf("      right: {\n        type: \"%d\",\n        value: \"%s\"\n      },\n", bin_expr->right->type, bin_expr->right->value);
            printf("      op: \"%s\"\n    }", bin_expr->op);
        }

        // Print a comma if not the last element
        if (i != program->body_size - 1)
        {
            printf(",");
        }
    }
    printf("\n  ]\n}\n");
}

#endif // PARSER_UTILS_C