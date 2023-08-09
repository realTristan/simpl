import Parser from "./parser.ts";
import { Program } from "./ast.ts";
import { evaluate } from "./runtime/interpreter.ts";
import Environment from "./runtime/env.ts";
import { RuntimeValue, NUMBER, NULL } from "./runtime/values.ts";

// Create a parser
const parser: Parser = new Parser();

// Initialize a new environment
const env: Environment = new Environment(null);

// Main.simpl file
const read = () => {
  const file = Deno.readTextFileSync("./main.simpl");

  // Produce AST From source-code
  const program = parser.parse(file);

  // Print the AST
  console.log(program);

  // Evaluate the program
  const result = evaluate(program, env);

  // Print the result
  console.log(result);
};

// Repl
const repl = () => {
  for (;;) {
    // Get the user input
    const input = prompt(">> ");

    // Check for no user input or exit keyword.
    if (!input || input === "exit") break;

    // Parse the input
    const program = parser.parse(input);

    // Print the AST
    console.log(program);

    // Get the result
    const result = evaluate(program, env);

    // Print the result
    console.log(result);
  }
};

// Read
read();

// Repl
repl();

// deno run --allow-read main.ts
