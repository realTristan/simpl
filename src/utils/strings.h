#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H

#include "../common/types.h"
#include <stdbool.h>

/**
 * @brief Checks if a string is alphabetical.
 * 
 * @param s The string to check.
 * @return true If the string is alphabetical.
 * @return false If the string is not alphabetical.
 */
bool is_alpha(string s);

/**
 * @brief Appends a character to a string.
 *
 * @param s The string to append to.
 * @param c The character to append.
 * @return string The appended string.
 */
string append_char(string s, char c);

/**
 * @brief Splits a string by a delimiter.
 * 
 * @param src The string to split.
 * @param delim The delimiter to split by.
 * @param count The amount of splits.
 * @return string* The split string.
 */
string *split(string src, char delim, int *count);

#endif // UTILS_STRINGS_H