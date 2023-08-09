import { isNumber, isString, isWhitespace } from "./utils.ts";

/**
 * A token type
 */
export enum TokenType {
  // Literals
  Null, // null
  Number, // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  Identifier, // x, y, z

  // Operators
  Equals, // =
  OpenParen, // (
  CloseParen, // )
  BinaryOperator, // +, -, *, /, %
  Semicolon, // ;
  EOF, // End of file
  Comma, // ,
  Colon, // :
  OpenBrace, // {
  CloseBrace, // }
  OpenBracket, // [
  CloseBracket, // ]
  Dot, // .

  // Variable declaration
  Let, // let
  Const, // const

  // Function declaration
  Function, // fn
}

/**
 * A map of reserved keywords
 */
const KEYWORDS: { [key: string]: TokenType } = {
  let: TokenType.Let,
  null: TokenType.Null,
  const: TokenType.Const,
  fn: TokenType.Function,
};

/**
 * A token
 */
export interface Token {
  value: string;
  type: TokenType;
}

/**
 * Tokenize the source code
 *
 * @param src The source code to tokenize
 * @returns An array of tokens
 * @throws An error if the token is invalid
 * @example
 * tokenize("let x = 5 + 5");
 * // => [
 * //   { value: "let", type: TokenType.Let },
 * //   { value: "x", type: TokenType.Identifier },
 * //   { value: "=", type: TokenType.Equals },
 * //   { value: "5", type: TokenType.Number },
 * //   { value: "+", type: TokenType.BinaryOperator },
 * //   { value: "5", type: TokenType.Number },
 * // ]
 */
export const tokenize = (src: string): Token[] => {
  const tokens: Token[] = new Array<Token>();
  const splitSrc: string[] = src.split("");

  // Loop through the source code
  while (splitSrc.length > 0) {
    // Get the value
    let value: string = splitSrc.shift()!;

    // Determine what type of token the value is
    switch (value) {
      case "=":
        tokens.push({ value: value, type: TokenType.Equals });
        break;
      case ";":
        tokens.push({ value: value, type: TokenType.Semicolon });
        break;
      case "(":
        tokens.push({ value: value, type: TokenType.OpenParen });
        break;
      case ")":
        tokens.push({ value: value, type: TokenType.CloseParen });
        break;
      case ",":
        tokens.push({ value: value, type: TokenType.Comma });
        break;
      case ":":
        tokens.push({ value: value, type: TokenType.Colon });
        break;
      case "{":
        tokens.push({ value: value, type: TokenType.OpenBrace });
        break;
      case "}":
        tokens.push({ value: value, type: TokenType.CloseBrace });
        break;
      case "[":
        tokens.push({ value: value, type: TokenType.OpenBracket });
        break;
      case "]":
        tokens.push({ value: value, type: TokenType.CloseBracket });
        break;
      case ".":
        tokens.push({ value: value, type: TokenType.Dot });
        break;
      case "+":
      case "-":
      case "*":
      case "/":
      case "%":
        tokens.push({ value: value, type: TokenType.BinaryOperator });
        break;
      default:
        // Get the current token
        const current = (): string => splitSrc[0];

        // Check if the value is a string
        if (isString(value)) {
          let str: string = value;
          while (splitSrc.length > 0 && isString(current())) {
            str += splitSrc.shift()!;
          }

          // Check for reserved keywords
          if (KEYWORDS[str.toLowerCase()]) {
            tokens.push({ value: str, type: KEYWORDS[str.toLowerCase()] });
          } else {
            tokens.push({ value: str, type: TokenType.Identifier });
          }
        }

        // Check if the value is a number
        else if (isNumber(value)) {
          let num: string = value;
          while (splitSrc.length > 0 && isNumber(current())) {
            num += splitSrc.shift()!;
          }

          // Push the number token
          tokens.push({ value: num, type: TokenType.Number });
        }

        // Else if the value is skippable
        else if (isWhitespace(value)) continue;
        // Throw an error if the value is neither a number or string
        else throw new Error(`Invalid token: ${value}`);
        break;
    }
  }

  // Push the EOF token
  // tokens.push({ value: "EOF", type: TokenType.EOF });

  // Return the array of tokens
  return tokens;
};
