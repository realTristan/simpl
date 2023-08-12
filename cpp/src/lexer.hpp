#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include "./utils.hpp"

/**
 * The type of token
 */
typedef enum TokenType
{
  Null,           // null
  Number,         // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  Identifier,     // x, y, z
  Equals,         // =
  OpenParen,      // (
  CloseParen,     // )
  BinaryOperator, // +, -, *, /, %
  Semicolon,      // ;
  Comma,          // ,
  Colon,          // :
  OpenBrace,      // {
  CloseBrace,     // }
  OpenBracket,    // [
  CloseBracket,   // ]
  Dot,            // .
  Let,            // let
  Const,          // const
  Function,       // fn
};

/**
 * Token Keywords
 */
const std::string keywords[] = {
    "let",
    "const",
    "fn",
    "null",
};

/**
 * Token type
 */
typedef struct Token
{
  TokenType type;
  std::string value;
} Token;

/**
 * Tokenizer class
 */
class Tokenizer
{

public:
  /**
   * Make a new token
   * @param type the token type
   * @param value the token value
   * @return Token*
   */
  static Token *new_token(TokenType type, std::string value)
  {
    Token *token = new Token();
    token->type = type;
    token->value = value;
    return token;
  }

  /**
   * Convert the source code into an array of tokens
   * @param src the source code (std string)
   * @return vector<Token*>
   */
  static std::vector<Token *> tokenize(std::string src)
  {
    // Store the tokens in a vector
    std::vector<Token *> tokens;

    // Iterate over the source code characters
    for (char c : src)
    {
      // Remove the character from the source code
      char value = Utils::shift_char(src);

      switch (c)
      {
      case '=':
        tokens.push_back(Tokenizer::new_token(TokenType::Equals, Utils::char_to_string(value)));
        break;

      case ';':
        tokens.push_back(Tokenizer::new_token(TokenType::Semicolon, Utils::char_to_string(value)));
        break;

      case '(':
        tokens.push_back(Tokenizer::new_token(TokenType::OpenParen, Utils::char_to_string(value)));
        break;

      case ')':
        tokens.push_back(Tokenizer::new_token(TokenType::CloseParen, Utils::char_to_string(value)));
        break;

      case ',':
        tokens.push_back(Tokenizer::new_token(TokenType::Comma, Utils::char_to_string(value)));
        break;

      case ':':
        tokens.push_back(Tokenizer::new_token(TokenType::Colon, Utils::char_to_string(value)));
        break;

      case '{':
        tokens.push_back(Tokenizer::new_token(TokenType::OpenBrace, Utils::char_to_string(value)));
        break;

      case '}':
        tokens.push_back(Tokenizer::new_token(TokenType::CloseBrace, Utils::char_to_string(value)));
        break;

      case '[':
        tokens.push_back(Tokenizer::new_token(TokenType::OpenBracket, Utils::char_to_string(value)));
        break;

      case ']':
        tokens.push_back(Tokenizer::new_token(TokenType::CloseBracket, Utils::char_to_string(value)));
        break;

      case '.':
        tokens.push_back(Tokenizer::new_token(TokenType::Dot, Utils::char_to_string(value)));
        break;

      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
        tokens.push_back(Tokenizer::new_token(TokenType::BinaryOperator, Utils::char_to_string(value)));
        break;

      default:
        // If the current value is a letter
        if (isalpha(value))
        {
          std::string res = "" + value;
          while (isalpha(src[0]))
          {
            res += Utils::shift_char(src);
          }

          if (res == "let")
          {
            tokens.push_back(Tokenizer::new_token(TokenType::Let, res));
          }
          else if (res == "const")
          {
            tokens.push_back(Tokenizer::new_token(TokenType::Const, res));
          }
          else if (res == "fn")
          {
            tokens.push_back(Tokenizer::new_token(TokenType::Function, res));
          }
          else if (res == "null")
          {
            tokens.push_back(Tokenizer::new_token(TokenType::Null, res));
          }
          else
          {
            tokens.push_back(Tokenizer::new_token(TokenType::Identifier, res));
          }
        }

        // If the current value is a number
        else if (Utils::isnum_char(value))
        {
          std::string res = "" + value;
          while (Utils::isnum_char(src[0]))
          {
            res += Utils::shift_char(src);
          }

          tokens.push_back(Tokenizer::new_token(TokenType::Number, res));
        }
      }
    }
  }
};

#endif // LEXER_HPP