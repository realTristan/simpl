import {
  BinaryExpr,
  Expr,
  Identifier,
  NumericLiteral,
  Program,
  Stmt,
} from "./ast.ts";
import { Token, TokenType, tokenize } from "./lexer.ts";

/**
 * A parser
 */
export default class Parser {
  // The tokens to parse
  private tokens: Token[] = [];

  /**
   * Get the current token
   * @returns Token
   */
  private get currentToken(): Token {
    return this.tokens[0];
  }

  /**
   * Check if the current token is additive
   * @returns boolean
   */
  private get currentTokenIsAdditive(): boolean {
    return (
      this.currentToken.type === TokenType.BinaryOperator &&
      (this.currentToken.value === "+" || this.currentToken.value === "-")
    );
  }

  /**
   * Check if the current token is multiplicative
   * @returns boolean
   */
  private get currentTokenIsMultiplicative(): boolean {
    return (
      this.currentToken.type === TokenType.BinaryOperator &&
      (this.currentToken.value === "*" ||
        this.currentToken.value === "/" ||
        this.currentToken.value === "%")
    );
  }

  /**
   * Produce a program from source code
   * @param src the source code
   * @returns Program
   */
  public parse(src: string): Program {
    // Convert the source into tokens
    this.tokens = tokenize(src);

    // Create a program
    const program: Program = {
      type: "Program",
      body: [],
    };

    // While there are still tokens to parse
    while (this.tokens.length > 0) {
      const stmt: Stmt = this.parseStmt();
      program.body.push(stmt);
    }

    // Return the program
    return program;
  }

  /**
   * Parse a statement
   * @returns Stmt
   */
  private parseStmt(): Stmt {
    return this.parseExpr();
  }

  /**
   * Parse an expression
   * @returns Expr
   */
  private parseExpr(): Expr {
    return this.parseAdditiveExpr();
  }

  /**
   * Parse a multiplicative expression
   * @returns Expr
   */
  private parseMultiplicativeExpr(): Expr {
    // Get the left side of the expression
    let left: Expr | BinaryExpr = this.parsePrimaryExpr();

    // While there are still tokens to parse
    while (this.tokens.length > 0 && this.currentTokenIsMultiplicative) {
      // Get the expression operator
      const op: Token = this.tokens.shift();

      // Get the right side of the expression
      const right: Expr = this.parsePrimaryExpr();

      // Create a binary expression
      const binexpr: BinaryExpr = {
        type: "BinaryExpr",
        operator: op.value,
        left: left,
        right: right,
      } as BinaryExpr;

      // Set the left to the new binary expression
      left = binexpr;
    }

    // Return the left side of the expression. We do this because
    // the left side becomes the entire binary expression
    return left;
  }

  /**
   * Parse a bianry expression
   * @returns Expr
   */
  private parseAdditiveExpr(): Expr {
    // Get the left side of the expression
    let left: Expr | BinaryExpr = this.parseMultiplicativeExpr();

    // While there are still tokens to parse
    while (this.tokens.length > 0 && this.currentTokenIsAdditive) {
      // Get the expression operator
      const op: Token = this.tokens.shift();

      // Get the right side of the expression
      const right: Expr = this.parsePrimaryExpr();

      // Create a binary expression
      const binexpr: BinaryExpr = {
        type: "BinaryExpr",
        operator: op.value,
        left: left,
        right: right,
      } as BinaryExpr;

      // Set the left to the new binary expression
      left = binexpr;
    }

    // Return the left side of the expression. We do this because
    // the left side becomes the entire binary expression
    return left;
  }

  /**
   * Handle a parenthesis
   * @returns Expr
   */
  private handleParen(): Expr {
    // Parse the expression without the open paren
    const expr: Expr = this.parseExpr();

    // Get the close paren and make sure it's valid. If it's
    // not, throw an error.
    const closeParen: Token = this.tokens.shift();
    if (closeParen.type !== TokenType.CloseParen) {
      throw new Error(`Unexpected token ${closeParen.value}`);
    }

    // Return the expression
    return expr;
  }

  /**
   * Parse a primary expression
   * @returns Expr
   */
  private parsePrimaryExpr(): Expr {
    const token: Token = this.tokens.shift();

    switch (token.type) {
      // Numeric Literal Expression
      case TokenType.Number:
        return {
          type: "NumericLiteral",
          value: parseFloat(token.value),
        } as NumericLiteral;

      // Identifier Expression
      case TokenType.Identifier:
        return {
          type: "Identifier",
          value: token.value,
        } as Identifier;

      // Let Statement
      case TokenType.Let:
        return {} as Expr;

      // Handle the open paren
      case TokenType.OpenParen:
        return this.handleParen();

      // Error
      default:
        throw new Error(`Unexpected token ${token.value}`);
    }
  }
}
