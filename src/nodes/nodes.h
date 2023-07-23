#ifndef NODES_H
#define NODES_H

#include "node_type.h"
#include <stdlib.h>

/**
 * @brief A statement node.
 *
 */
typedef struct Stmt
{
    NodeType type;
    char *value;
} Stmt;

/**
 * @brief A program node.
 *
 */
typedef struct Program
{
    NodeType type; // NODE_TYPE_PROGRAM
    Stmt **body;
    size_t body_size;
} Program;

/**
 * @brief An expression node.
 *
 */
typedef struct Expr
{
    NodeType type;
    char* value;
} Expr;

/**
 * @brief A binary expression node.
 *
 */
typedef struct BinaryExpr
{
    NodeType type; // NODE_TYPE_BINARY_EXPRESSION
    Expr *left;
    Expr *right;
    char *op;
} BinaryExpr;

/**
 * @brief An identifier node.
 *
 */
typedef struct Identifier
{
    NodeType type; // NODE_TYPE_IDENTIFIER
    char *symbol;
} Identifier;

/**
 * @brief An numeric literal node.
 *
 */
typedef struct NumericLiteral
{
    NodeType type;
    double value;
} NumericLiteral;

#endif // NODES_H