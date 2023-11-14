#include "main.h"
/**
 * custom_printf - Enhanced printf function.
 * @format: Format string.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
    int i, printed_chars = 0, format_chars = 0;
    int flags, width, precision, size, buff_index = 0;
    va_list args;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return -1;

    va_start(args, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_index++] = format[i];
            if (buff_index == BUFF_SIZE)
                buffer_print(buffer, &buff_index);
            printed_chars++;
        }
        else
        {
            buffer_print(buffer, &buff_index);
            flags = extract_flags(format, &i);
            width = get_width(format, &i, args);
            precision = get_precision(format, &i, args);
            size = get_size(format, &i);
            ++i;
            if (format[i] == 'r')
            {
                format_chars = handle_unknown_format(buffer, &buff_index);
            }
            else
            {
                format_chars = print_with_format(format, &i, args, buffer,
                                              flags, width, precision, size);
            }
            if (format_chars == -1)
                return -1;
            printed_chars += format_chars;
        }
    }

    buffer_print(buffer, &buff_index);

    va_end(args);

    return printed_chars;
}

/**
 * handle_unknown_format - Process unknown format specifiers.
 * @buff: Character buffer.
 * @buff_index: Pointer to buffer index.
 * Return: Number of characters printed for unknown format.
 */
int handle_unknown_format(char buff[], int *buff_index)
{
    int len = 0;
    len += append_to_buffer(buff, buff_index, "%r");
    return len;
}

/**
 * buffer_print - Print the contents of the buffer.
 * @buff: Character buffer.
 * @buff_index: Pointer to buffer index.
 */
void buffer_print(char buff[], int *buff_index)
{
    if (*buff_index > 0)
        write(1, &buff[0], *buff_index);

    *buff_index = 0;
}

/**
 * append_to_buffer - Append a string to the buffer.
 * @buff: Character buffer.
 * @buff_index: Pointer to buffer index.
 * @str: String to append.
 * Return: Number of characters appended.
 */
int append_to_buffer(char buff[], int *buff_index, const char *str)
{
    int len = 0;
    int i = 0;

    if (buff == NULL || buff_index == NULL || str == NULL)
        return -1;

    while (str[i] != '\0')
    {
        buff[*buff_index] = str[i];
        (*buff_index)++;
        len++;
        i++;
    }

    return len;
}
