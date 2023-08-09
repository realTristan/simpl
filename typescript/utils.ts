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
export const isNumber = (value: string): boolean => {
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
export const isString = (value: string): boolean => {
  return value.match(/[a-z]/i) ? true : false;
};

/**
 * Check if the value is a whitespace character
 * @param value The value to check
 * @returns True if the value is a whitespace character, false otherwise
 */
export const isWhitespace = (value: string): boolean => {
  return value === " " || value === "\n" || value === "\t" || value === "\r";
};
