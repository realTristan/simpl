#ifndef NODE_TYPE_H
#define NODE_TYPE_H

/**
 * @brief The type of a node.
 *
 * @details
 * The type of a node is used to determine what kind of node it is.
 * This is useful for determining how to handle a node.
 *
 */
typedef enum NodeType
{
    // Currently in use
    NODE_TYPE_PROGRAM,
    NODE_TYPE_BINARY_EXPRESSION,
    NODE_TYPE_REGULAR_EXPRESSION,
    NODE_TYPE_NUMERIC_LITERAL,
    NODE_TYPE_NULL_LITERAL,
    NODE_TYPE_IDENTIFIER,

    // Currently Unused
    NODE_TYPE_STATEMENT,
    NODE_TYPE_INTEGER_LITERAL,
    NODE_TYPE_STRING_LITERAL,
    NODE_TYPE_BOOLEAN_LITERAL,
    NODE_TYPE_FLOAT_LITERAL,
    NODE_TYPE_FUNCTION_CALL,
    NODE_TYPE_FUNCTION_DECLARATION,
    NODE_TYPE_FUNCTION_PARAMETER,
    NODE_TYPE_VARIABLE_DECLARATION,
    NODE_TYPE_VARIABLE_ASSIGNMENT,
    NODE_TYPE_VARIABLE_REFERENCE,
    NODE_TYPE_UNARY_EXPRESSION,
    NODE_TYPE_CONDITIONAL_EXPRESSION,
    NODE_TYPE_CONDITIONAL_STATEMENT,
    NODE_TYPE_LOOP_STATEMENT,
    NODE_TYPE_RETURN_STATEMENT,
    NODE_TYPE_BREAK_STATEMENT,
    NODE_TYPE_CONTINUE_STATEMENT,
    NODE_TYPE_BLOCK,
    NODE_TYPE_ARRAY_LITERAL,
    NODE_TYPE_ARRAY_SUBSCRIPT,
    NODE_TYPE_ARRAY_SLICE,
    NODE_TYPE_ARRAY_PUSH,
    NODE_TYPE_ARRAY_POP,
    NODE_TYPE_ARRAY_LENGTH,
    NODE_TYPE_ARRAY_INSERT,
    NODE_TYPE_ARRAY_REMOVE,
    NODE_TYPE_ARRAY_INDEX_OF,
    NODE_TYPE_ARRAY_REVERSE,
    NODE_TYPE_ARRAY_SORT,
    NODE_TYPE_ARRAY_MAP,
    NODE_TYPE_ARRAY_FILTER,
    NODE_TYPE_ARRAY_REDUCE,
    NODE_TYPE_ARRAY_FIND,
    NODE_TYPE_ARRAY_FIND_INDEX,
    NODE_TYPE_ARRAY_FILL,
    NODE_TYPE_ARRAY_COPY,
    NODE_TYPE_ARRAY_CONTAINS,
    NODE_TYPE_ARRAY_JOIN,
    NODE_TYPE_ARRAY_FLATTEN,
    NODE_TYPE_ARRAY_UNIQUE,
    NODE_TYPE_ARRAY_SLICE_FROM,
    NODE_TYPE_ARRAY_SLICE_TO,
    NODE_TYPE_ARRAY_SLICE_RANGE,
    NODE_TYPE_ARRAY_SPLICE,
} NodeType;

#endif // NODE_TYPE_H