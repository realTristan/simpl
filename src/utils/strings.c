#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H

#include "../common/types.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Splits a string by a delimiter.
 * 
 * @param src The string to split.
 * @param delim The delimiter to split by.
 * @return string* The split string.
 */
string *split(string src, string delim)
{
    string *res = malloc(sizeof(string));
    string token = strtok(src, delim);

    while (token != NULL)
    {
        res[sizeof(res) + 1] = token;
        token = strtok(NULL, delim);
    }
    return res;
}

/**
 * @brief Checks if a character is a digit.
 * 
 * @param c The character to check.
 * @return true If the character is a digit.
 * @return false If the character is not a digit.
 */
bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

#endif // UTILS_STRING_H