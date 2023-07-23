#ifndef UTILS_C
#define UTILS_C

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Checks if a character is an integer.
 *
 * @param s The string to check.
 * @return true If the character is an integer.
 * @return false If the character is not an integer.
 */
bool is_int(char *s)
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

/**
 * @brief Checks if a character is a digit.
 *
 * @param s The string to check.
 * @return true If the character is a digit.
 * @return false If the character is not a digit.
 */
bool is_alpha(char *s)
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
 * @brief Splits a string by a delimiter.
 *
 * @param s The string to split.
 * @param delim The delimiter to split by.
 * @param count The amount of splits.
 * @return char** The split string.
 */
char **split_str(char *s, char delim, int *count)
{
    // Get the length of the src
    long long len = strlen(s);

    // Create the result array
    char **res = malloc(sizeof(char *) * len);

    // Store the last index (for determining splits)
    int last_index = 0;

    // Iterate over the string
    for (unsigned int i = 0; i < len; i++)
    {
        // If the current character is the delimiter
        int is_last = (i + 1 == len);
        if (s[i] == delim || is_last)
        {
            // Get the value from the last index to the current index
            char *tmp = malloc(sizeof(char) * (i - last_index));
            for (unsigned int j = last_index; j < i + is_last; j++)
            {
                if (s[j] == delim)
                    break;
                tmp[j - last_index] = s[j];
            }
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
    char **final_res = malloc(*count * sizeof(char *));
    for (unsigned int i = 0; i < *count; i++)
        final_res[i] = res[i];

    // Free the res array
    free(res);

    // Return the final result
    return final_res;
}

#endif // UTILS_C