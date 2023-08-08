import Parser from "./parser.ts";
import { Program } from "./ast.ts";
import { evaluate } from "./runtime/interpreter.ts";

// Source code to parse
const src: string = "2 + 5 * 2";

// Create a parser
const parser: Parser = new Parser();

// Parse the source code
const program: Program = parser.parse(src);

// Print the AST
console.log(program);

// Evaluate the AST
const result = evaluate(program);

// Print the result
console.log(result);

// deno run main.ts
