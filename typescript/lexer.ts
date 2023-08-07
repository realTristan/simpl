/**
 * Simpl_TS is a basic programming langauge written in typescript.
 * It uses the same logic as my simpl language written in C.
 * I got stuck and decided to use a more OOP language to help me
 * understand the concepts better.
 */

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

const Keywords: { [key: string]: TokenType } = {
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
 * Check if the value is a number
 *
 * @param value The value to check
 * @returns True if the value is a number, false otherwise
 * @example
 * isNumber("5");
 * // => true
 * isNumber("hello");
 * // => false
 */
const isNumber = (value: string): boolean => {
  return value.match(/[0-9]/i) ? true : false;
};

/**
 * Check if the value is a string
 *
 * @param value The value to check
 * @returns True if the value is a string, false otherwise
 * @example
 * isString("hello");
 * // => true
 * isString("5");
 * // => false
 */
const isString = (value: string): boolean => {
  return value.match(/[a-z]/i) ? true : false;
};

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
  const src_split: string[] = src.split(" ");

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
        tokens.push({ value: value, type: TokenType.BinaryOperator });
        break;
      default:
        // Check if the value is a string
        if (isString(value)) {
          // Check for reserved keywords
          if (Keywords[value.toLowerCase()])
            tokens.push({ value: value, type: Keywords[value.toLowerCase()] });
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

// Run the lexer
const tokens = tokenize("let x = 5 + 5");
console.log(tokens);

// deno run lexer.ts
