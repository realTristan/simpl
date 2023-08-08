import { isNumber, isString } from "./utils.ts";

/**
 * A token type
 */
export enum TokenType {
  Number,
  Identifier,
  Equals,
  OpenParen,
  CloseParen,
  BinaryOperator,
  Let,
}

/**
 * A map of reserved keywords
 */
const KEYWORDS: { [key: string]: TokenType } = {
  let: TokenType.Let,
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
  const src_split: string[] = src.split("");

  // Loop through the source code
  while (src_split.length > 0) {
    // Get the value
    let value: string = src_split.shift()!;

    // Determine what type of token the value is
    switch (value) {
      case "=":
        tokens.push({ value: value, type: TokenType.Equals });
        break;
      case "(":
        tokens.push({ value: value, type: TokenType.OpenParen });
        break;
      case ")":
        tokens.push({ value: value, type: TokenType.CloseParen });
        break;
      case "+":
      case "-":
      case "*":
      case "/":
      case "%":
        tokens.push({ value: value, type: TokenType.BinaryOperator });
        break;
      default:
        // Check if the value is a string
        if (isString(value)) {
          // Check for reserved keywords
          if (KEYWORDS[value.toLowerCase()])
            tokens.push({ value: value, type: KEYWORDS[value.toLowerCase()] });
          else tokens.push({ value: value, type: TokenType.Identifier });
        }

        // Check if the value is a number
        else if (isNumber(value))
          tokens.push({ value: value, type: TokenType.Number });
        // Else if the value is skippable
        else if (value.match(/\s/)) continue;
        // Throw an error if the value is neither a number or string
        else throw new Error(`Invalid token: ${value}`);
        break;
    }
  }

  // Return the array of tokens
  return tokens;
};
