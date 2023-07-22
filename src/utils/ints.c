#ifndef UTILS_INTS_C
#define UTILS_INTS_C

#include <stdbool.h>

/**
 * @brief Checks if a character is an integer.
 * 
 * @param c The character to check.
 * @return true If the character is an integer.
 * @return false If the character is not an integer.
 */
bool is_int(char c)
{
    return c >= '0' && c <= '9';
}

#endif // UTILS_INTS_C