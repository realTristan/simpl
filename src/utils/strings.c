#ifndef UTILS_STRINGS_C
#define UTILS_STRINGS_C

#include "../common/types.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Checks if a character is a digit.
 *
 * @param s The string to check.
 * @return true If the character is a digit.
 * @return false If the character is not a digit.
 */
bool is_alpha(string s)
{
    for (unsigned int i = 0; i < strlen(s); i++)
    {
        if ((s[i] < 'a' && s[i] < 'z') || (s[i] < 'A' && s[i] < 'Z'))
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Appends a character to a string.
 *
 * @param s The string to append to.
 * @param c The character to append.
 * @return string The appended string.
 */
string append_char(string s, char c)
{
    // Get the length of the string
    long long len = strlen(s);

    // Allocate a new string with +1 length
    string res = malloc(sizeof(char) * (len + 2));

    // Copy the string to the result
    for (unsigned int i = 0; i < len; i++)
        res[i] = s[i];

    // Append the character to the result
    res[len] = c;
    res[len + 1] = '\0';

    // Return the result
    return res;
}

/**
 * @brief Splits a string by a delimiter.
 *
 * @param src The string to split.
 * @param delim The delimiter to split by.
 * @param count The amount of splits.
 * @return string* The split string.
 */
string *split(string src, char delim, int *count)
{
    // Get the length of the src
    long long len = strlen(src);

    // Create the result array
    string *res = malloc(sizeof(string) * len);

    // Store the last index (for determining splits)
    int last_index = 0;

    // Iterate over the string
    for (unsigned int i = 0; i < len; i++)
    {
        // If the current character is the delimiter
        int is_last = (i + 1 == len);
        if (src[i] == delim || is_last)
        {
            // Get the value from the last index to the current index
            char *tmp = malloc(sizeof(char) * (i - last_index));
            for (unsigned int j = last_index; j < i + is_last; j++)
                tmp[j - last_index] = src[j];
            tmp[i - last_index + is_last] = '\0';

            // Add the tmp to the result array
            res[*count] = tmp;

            // Update the last index
            last_index = i + 1;

            // Increment the total split count
            *count = *count + 1;
        }
    }

    // Create a copy of the resutl array with only the correct size
    string *final_res = malloc(*count * sizeof(string));
    for (unsigned int i = 0; i < *count; i++)
        final_res[i] = res[i];

    // Free the res array
    free(res);

    // Return the final result
    return final_res;
}

#endif // UTILS_STRINGS_C