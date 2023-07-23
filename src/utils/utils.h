#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * @brief Checks if a character is an integer.
 *
 * @param s The string to check.
 * @return true If the character is an integer.
 * @return false If the character is not an integer.
 */
bool is_int(char *s);

/**
 * @brief Checks if a string is alphabetical.
 *
 * @param s The string to check.
 * @return true If the string is alphabetical.
 * @return false If the string is not alphabetical.
 */
bool is_alpha(char *s);

/**
 * @brief Splits a string by a delimiter.
 *
 * @param s The string to split.
 * @param delim The delimiter to split by.
 * @param count The amount of splits.
 * @return string* The split string.
 */
char **split_str(char *s, char delim, int *count);

#endif // UTILS_H