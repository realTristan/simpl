#ifndef TOKEN_H
#define TOKEN_H

/**
 * @brief The type of a token.
 *
 * @details
 * The type of a token is used to determine how to interpret the value of a token.
 * For example, if the type of a token is TOKEN_TYPE_NUMBER, then the value of the
 * token is a string representation of a number. If the type of a token is
 * TOKEN_TYPE_PLUS, then the value of the token is the string "+".
 *
 */
typedef enum token_type
{
    TOKEN_TYPE_NULL,
    TOKEN_TYPE_LET,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_BINARY_OPERATOR,
    TOKEN_TYPE_LEFT_PAREN,
    TOKEN_TYPE_RIGHT_PAREN,
    TOKEN_TYPE_LEFT_BRACE,
    TOKEN_TYPE_RIGHT_BRACE,
    TOKEN_TYPE_LEFT_BRACKET,
    TOKEN_TYPE_RIGHT_BRACKET,
    TOKEN_TYPE_COMMA,
    TOKEN_TYPE_SEMICOLON,
    TOKEN_TYPE_COLON,
    TOKEN_TYPE_DOT,
    TOKEN_TYPE_ASSIGN,
    TOKEN_TYPE_EQUAL,
    TOKEN_TYPE_NOT_EQUAL,
    TOKEN_TYPE_LESS_THAN,
    TOKEN_TYPE_LESS_THAN_EQUAL,
    TOKEN_TYPE_GREATER_THAN,
    TOKEN_TYPE_GREATER_THAN_EQUAL,
    TOKEN_TYPE_PLUS_ASSIGN,
    TOKEN_TYPE_MINUS_ASSIGN,
    TOKEN_TYPE_MULTIPLY_ASSIGN,
    TOKEN_TYPE_DIVIDE_ASSIGN,
    TOKEN_TYPE_MODULO_ASSIGN,
    TOKEN_TYPE_BITWISE_AND_ASSIGN,
    TOKEN_TYPE_BITWISE_OR_ASSIGN,
    TOKEN_TYPE_BITWISE_XOR_ASSIGN,
    TOKEN_TYPE_BITWISE_NOT_ASSIGN,
    TOKEN_TYPE_LOGICAL_AND,
    TOKEN_TYPE_LOGICAL_OR,
    TOKEN_TYPE_LOGICAL_NOT,
    TOKEN_TYPE_BITWISE_AND,
    TOKEN_TYPE_BITWISE_OR,
    TOKEN_TYPE_BITWISE_XOR,
    TOKEN_TYPE_BITWISE_NOT,
    TOKEN_TYPE_MODULO,
    TOKEN_TYPE_INCREMENT,
    TOKEN_TYPE_DECREMENT,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_CHARACTER,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE,
    TOKEN_TYPE_WHITESPACE,
    TOKEN_TYPE_UNKNOWN,
    TOKEN_TYPE_EOF
} token_type;

/**
 * @brief A token is a pair of a token type and a value.
 *
 * @param type The type of the token.
 * @param value The value of the token.
 */
typedef struct token_t
{
    token_type type;
    char *value;
} token_t;

/**
 * @brief Makes a token.
 *
 * @param type The token type.
 * @param value The token value.
 * @return token_t The token.
 */
token_t new_token(token_type type, char *value);
token_t new_token_char(token_type type, char value);

#endif // TOKEN_H