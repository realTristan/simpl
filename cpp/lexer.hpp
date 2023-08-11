#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

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
private:
  char shift(std::string &src)
  {
    // Get the first character
    char c = src[0];

    // Remove the first character
    src.erase(src.begin());

    // Return the first character
    return c;
  }

  bool isalpha(char c)
  {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }

  bool isnum(char c)
  {
    return c >= '0' && c <= '9';
  }

public:
  std::vector<Token> tokenize(std::string src)
  {
    // Store the tokens in a vector
    std::vector<Token> tokens;

    // Iterate over the source code characters
    for (char c : src)
    {
      // Remove the character from the source code
      char value = shift(src);

      switch (c)
      {
      case '=':
        tokens.push_back({TokenType::Equals, &value});
        break;

      case ';':
        tokens.push_back({TokenType::Semicolon, &value});
        break;

      case '(':
        tokens.push_back({TokenType::OpenParen, &value});
        break;

      case ')':
        tokens.push_back({TokenType::CloseParen, &value});
        break;

      case ',':
        tokens.push_back({TokenType::Comma, &value});
        break;

      case ':':
        tokens.push_back({TokenType::Colon, &value});
        break;

      case '{':
        tokens.push_back({TokenType::OpenBrace, &value});
        break;

      case '}':
        tokens.push_back({TokenType::CloseBrace, &value});
        break;

      case '[':
        tokens.push_back({TokenType::OpenBracket, &value});
        break;

      case ']':
        tokens.push_back({TokenType::CloseBracket, &value});
        break;

      case '.':
        tokens.push_back({TokenType::Dot, &value});
        break;

      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
        tokens.push_back({TokenType::BinaryOperator, &value});
        break;

      default:
        // If the current value is a letter
        if (isalpha(value))
        {
          std::string res = "" + value;
          while (isalpha(src[0]))
          {
            res += shift(src);
          }

          if (res == "let")
          {
            tokens.push_back({TokenType::Let, res});
          }
          else if (res == "const")
          {
            tokens.push_back({TokenType::Const, res});
          }
          else if (res == "fn")
          {
            tokens.push_back({TokenType::Function, res});
          }
          else if (res == "null")
          {
            tokens.push_back({TokenType::Null, res});
          }
          else
          {
            tokens.push_back({TokenType::Identifier, res});
          }
        }

        // If the current value is a number
        else if (isnum(value))
        {
          std::string res = "" + value;
          while (isnum(src[0]))
          {
            res += shift(src);
          }

          tokens.push_back({TokenType::Number, res});
        }
      }
    }
  }
};

#endif // LEXER_HPP