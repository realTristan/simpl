#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>

class Utils
{
public:
    /**
     * Convert a char to a string
     * @param c the character
     * @return string
     */
    static std::string char_to_string(char c)
    {
        return "" + c;
    }

    /**
     * Shift the character
     * @param src the source string (pointer)
     * @return char
     */
    static char shift_char(std::string &src)
    {
        // Get the first character
        char c = src[0];

        // Remove the first character
        src.erase(src.begin());

        // Return the first character
        return c;
    }

    /**
     * Check if the provided character is alpha
     * @param c the character
     * @return bool
     */
    static bool isalpha_char(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    /**
     * Check if the provided character is a number
     * @param c the character
     * @return bool
     */
    static bool isnum_char(char c)
    {
        return c >= '0' && c <= '9';
    }
};

#endif // UTILS_HPP