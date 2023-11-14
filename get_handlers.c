#include "main.h"
/**
 * extract_flags - Extract active flags from a formatted string.
 * @format: The formatted string containing the flags.
 * @i: The current position in the string.
 * Return: The extracted flags.
 */
int extract_flags(const char *format, int *i)
{
	int j, currIndex;
	int flags = 0;
	const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (currIndex = *i + 1; format[currIndex] != '\0'; currIndex++) {
		for (j = 0; FLAGS_CHARACTERS[j] != '\0'; j++)
			if (format[currIndex] == FLAGS_CHARACTERS[j]) {
				flags |= FLAGS_ARRAY[j];
				break;
			}

		if (FLAGS_CHARACTERS[j] == 0)
			break;
	}

	*i = currIndex - 1;

	return (flags);
}
/**
 * get_precision - Determine the precision for formatting a string.
 * @format: The format string for the argument list.
 * @i: The index of the current argument.
 * @list: A list of arguments.
 *
 * Return: The calculated precision value.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int currIndex = *i + 1;
	int precision = -1;

	if (format[currIndex] != '.')
		return (precision);

	precision = 0;

	for (currIndex += 1; format[currIndex] != '\0'; currIndex++) {
		if (is_digit(format[currIndex])) {
			precision *= 10;
			precision += format[currIndex] - '0';
		} else if (format[currIndex] == '*') {
			currIndex++;
			precision = va_arg(list, int);
			break;
		} else
			break;
	}

	*i = currIndex - 1;

	return (precision);
}
/**
 * get_size - Determine the required size
 * for casting the argument.
 * @format: The format string for printing the arguments.
 * @i: Index of the argument in the list.
 *
 * Return: The calculated size for casting the argument.
 */
int get_size(const char *format, int *i)
{
	int currIndex = *i + 1;
	int size = 0;

	if (format[currIndex] == 'l')
		size = S_LONG;
	else if (format[currIndex] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = currIndex - 1;
	else
		*i = currIndex;

	return (size);
}
/**
 * get_width - Determine the required
 * width for formatting and printing.
 * @format: The format string for printing the arguments.
 * @i: Index of the argument in the list.
 * @list: List of arguments to be printed.
 *
 * Return: The calculated printing width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int currIndex;
	int width = 0;

	for (currIndex = *i + 1; format[currIndex] != '\0'; currIndex++) {
		if (is_digit(format[currIndex])) {
			width *= 10;
			width += format[currIndex] - '0';
		} else if (format[currIndex] == '*') {
			currIndex++;
			width = va_arg(list, int);
			break;
		} else
			break;
	}

	*i = currIndex - 1;

	return (width);
}