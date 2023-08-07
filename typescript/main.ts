import { tokenize } from "./lexer.ts";

// Run the lexer
const tokens = tokenize("let x = 5 + 5");
console.log(tokens);

// deno run main.ts