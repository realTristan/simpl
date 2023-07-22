#ifndef LEXER_C
#define LEXER_C

#include "token/token.h"
#include "token/token_type.h"

#include "../common/types.h"
#include "../utils/strings.h"
#include "../utils/ints.h"

#include <string.h>
#include <stdio.h>

/**
 * @brief Pushes a token to the back of a token array.
 *
 * @param tokens The token array.
 * @param token The token to push.
 */
void push_back(Token tokens[], Token token)
{
    tokens[sizeof(tokens) + 1] = token;
}

/**
 * @brief Pops a token from the front of a token array.
 *
 * @param tokens The token array.
 * @return Token The popped token.
 */
string pop(string *tokens)
{
    string res = tokens[0];
    for (int i = 1; i < sizeof(tokens); i++)
    {
        tokens[i - 1] = tokens[i];
    }
    return res;
}

/**
 * @brief Tokenizes a string.
 *
 * @param src The string to tokenize.
 * @return const Token* The tokens.
 */
Token *tokenize(string src)
{
    // The list of tokens
    Token tokens[] = {};

    // Split the src
    string *split_src = split(src, " ");

    // Build each token
    while (sizeof(split_src) > 0)
    {
        // Pop the token
        string token = pop(split_src);

        // Check the token type
        if (token == ' ' || token == '\n' || token == '\t')
        {
            continue;
        }
        else if (token == '(')
        {
            push_back(tokens, (Token){TOKEN_TYPE_LEFT_PAREN, "("});
        }
        else if (token == ')')
        {
            push_back(tokens, (Token){TOKEN_TYPE_RIGHT_PAREN, ")"});
        }
        else if (token == '=')
        {
            push_back(tokens, (Token){TOKEN_TYPE_EQUAL, "="});
        }
        else if (token == '+')
        {
            push_back(tokens, (Token){TOKEN_TYPE_PLUS, "+"});
        }
        else if (token == '-')
        {
            push_back(tokens, (Token){TOKEN_TYPE_MINUS, "-"});
        }
        else if (token == '*')
        {
            push_back(tokens, (Token){TOKEN_TYPE_MULTIPLY, "*"});
        }
        else if (token == '/')
        {
            Token token = {TOKEN_TYPE_DIVIDE, "/"};
            push_back(tokens, token);
        }
        else
        {
            if (is_int(token))
            {
                string num = "";
                while (sizeof(split_src) > 0 && is_int(split_src[0]))
                {
                    string n = pop(split_src);
                    num = strcat(num, n);
                }
                push_back(tokens, (Token){TOKEN_TYPE_NUMBER, num});
            }
            else if (is_alpha(token))
            {
                string str = "";
                while (sizeof(split_src) > 0 && is_alpha(split_src[0]))
                {
                    string n = pop(split_src);
                    str = strcat(str, n);
                }
                if (token == "let")
                {
                    push_back(tokens, (Token){TOKEN_TYPE_LET, "let"});
                }
                else
                {
                    push_back(tokens, (Token){TOKEN_TYPE_IDENTIFIER, str});
                }
            }
            else
            {
                return tokens;
            }
        }
    }

    return tokens;
}

#endif // LEXER_C