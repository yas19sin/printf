#include "main.h"
/**
 * is_printable - Determine if a character is printable.
 * @c: The character to evaluate.
 *
 * Return: 1 if 'c' is printable, 0 otherwise.
 */
int is_printable(char c)
{
    return (c >= 32 && c < 127);
}

/**
 * is_digit - Determine if a character is a digit.
 * @c: The character to evaluate.
 *
 * Return: 1 if 'c' is a digit, 0 otherwise.
 */
int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

/**
 * hex_code - Appends ASCII in hexadecimal
 * representation to a buffer.
 * @buffer: Array of characters.
 * @i: Index at which to start appending.
 * @asciiCode: ASCII code.
 * Return: Always 3 (the number of characters appended).
 */
int hex_code(char asciiCode, char buffer[], int i) {
    const char HEX_MAP[] = "0123456789ABCDEF";

    if (asciiCode < 0)
        asciiCode *= -1;

    buffer[i++] = '\\';
    buffer[i++] = 'x';

    buffer[i++] = HEX_MAP[asciiCode / 16];
    buffer[i] = HEX_MAP[asciiCode % 16];

    return 3;
}

/**
 * convert_size_number - Convert a number to the specified data type.
 * @num: The number to be converted.
 * @size: An integer indicating the data type for the conversion.
 *
 * Return: The value of 'num' after conversion.
 */
long int convert_size_number(long int num, int size) {
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (short)num;

    return (int)num;
}

/**
 * convert_size_unsigned - Convert a number to the specified data type.
 * @num: The number to be converted.
 * @size: An integer indicating the target data type for the conversion.
 *
 * Return: The value of 'num' after conversion.
 */
long int convert_size_unsigned(unsigned long int num, int size) {
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (unsigned short)num;

    return (unsigned int)num;
}