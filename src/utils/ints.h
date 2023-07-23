#ifndef UTILS_INTS_H
#define UTILS_INTS_H

#include "../common/types.h"

#include <stdbool.h>

/**
 * @brief Checks if a character is an integer.
 * 
 * @param s The string to check.
 * @return true If the character is an integer.
 * @return false If the character is not an integer.
 */
bool is_int(string s);

#endif // UTILS_INTS_H