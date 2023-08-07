#ifndef UTILS_C
#define UTILS_C

#include <string.h>
#include <stdlib.h>

/**
 * Split Array
 */
typedef struct split_array_t
{
    char **values;
    size_t size;
} split_array_t;

/**
 * @brief Checks if a character is an integer.
 *
 * @param s The string to check.
 * @return true If the character is an integer.
 * @return false If the character is not an integer.
 */
int is_int(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Checks if a character is a digit.
 *
 * @param s The string to check.
 * @return true If the character is a digit.
 * @return false If the character is not a digit.
 */
int is_alpha(char *s)
{
    for (unsigned int i = 0; i < strlen(s); i++)
    {
        if ((s[i] < 'a' && s[i] < 'z') || (s[i] < 'A' && s[i] < 'Z'))
        {
            return 0;
        }
    }
    return 1;
}

/**
 * Free the split array.
 * 
 * @param split_array The split array.
 * @return void
 */
void free_split_array(split_array_t split_array)
{
    for (unsigned int i = 0; i < split_array.size; i++)
    {
        free(split_array.values[i]);
    }
    free(split_array.values);
}

/**
 * @brief Splits a string by a delimiter.
 *
 * @param s The string to split.
 * @param delim The delimiter to split by.
 * @return split_array_t The split string.
 */
split_array_t split_str(char *s, char delim)
{
    // Get the length of the src
    long long len = strlen(s);

    // Create the result array
    split_array_t res = {malloc(sizeof(char *) * len), 0};

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
            char *tmp = malloc(sizeof(char) * (i - last_index + is_last));
            for (unsigned int j = last_index; j < i + is_last; j++)
            {
                if (s[j] == delim)
                    break;
                tmp[j - last_index] = s[j];
            }
            tmp[i - last_index + is_last] = '\0';

            // Add the tmp to the result array
            res.values[res.size] = tmp;

            // Update the last index
            last_index = i + 1;

            // Increment the total split size
            res.size++;
        }
    }

    // Create a copy of the resut array with only the correct size
    split_array_t final_res = {malloc(sizeof(char *) * res.size), res.size};
    for (unsigned int i = 0; i < res.size; i++)
    {
        final_res.values[i] = res.values[i];
    }

    // Return the final result
    return final_res;
}

#endif // UTILS_C