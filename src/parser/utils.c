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
    printf("{ type:\"%d\"", program->type);
    printf(", body:[");
    for (int i = 0; i < program->body_size; i++)
    {
        // Print the expressions
        /*
            NodeType type;
            char *value;

            // Binary Expressions
            struct Expr *left;
            struct Expr *right;
            char *op;
        */
        if (program->body[i]->type != NODE_TYPE_BINARY_EXPRESSION)
        {
            printf("{ type:\"%d\", value:\"%s\" }", program->body[i]->type, program->body[i]->value);
        }
        else
        {
            printf("{ left:{ type:\"%d\", value:\"%s\" }, right:{ type:\"%d\", value:\"%s\" }, op:\"%s\" }",
                   program->body[i]->left->type, program->body[i]->left->value,
                   program->body[i]->right->type, program->body[i]->right->value,
                   program->body[i]->op);
        }

        // Print a comma if not the last element
        if (i != program->body_size - 1)
        {
            printf(",");
        }
    }
    printf("] }");
}

#endif // PARSER_UTILS_C