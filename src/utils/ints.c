#ifndef UTILS_INTS_C
#define UTILS_INTS_C

#include "../common/types.h"

#include <stdbool.h>
#include <string.h>

/**
 * @brief Checks if a character is an integer.
 * 
 * @param s The string to check.
 * @return true If the character is an integer.
 * @return false If the character is not an integer.
 */
bool is_int(string s)
{
    long long len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}

#endif // UTILS_INTS_C