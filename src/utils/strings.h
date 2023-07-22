#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H

#include "../common/types.h"
#include <stdbool.h>

/**
 * @brief Splits a string by a delimiter.
 * 
 * @param src The string to split.
 * @param delim The delimiter to split by.
 * @return string* The split string.
 */
string *split(string src, string delim);

/**
 * @brief Checks if a character is a digit.
 * 
 * @param c The character to check.
 * @return true If the character is a digit.
 * @return false If the character is not a digit.
 */
bool is_alpha(char c);

#endif // UTILS_STRING_H