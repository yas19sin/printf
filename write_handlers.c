#include "main.h"
/**
 * write_char - Print a character.
 * @c: The character to print.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char iPadd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		iPadd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = iPadd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_numbers - Print a number.
 * @is_negative: Indicator for a negative number.
 * @ind: Character types.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_numbers(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int iLength = BUFF_SIZE - ind - 1;
	char iPadd = ' ', extraCh = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		iPadd = '0';
	if (is_negative)
		extraCh = '-';
	else if (flags & F_PLUS)
		extraCh = '+';
	else if (flags & F_SPACE)
		extraCh = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		iLength, iPadd, extraCh));
}

/**
 * write_num - Write a number into a buffer.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: The buffer.
 * @flags: Flags for formatting.
 * @width: Width specifier.
 * @prec: Precision specifier.
 * @length: Length of the number.
 * @padd: Padding character.
 * @extra_c: Extra character.
 *
 * Return: The number of characters printed.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, iPaddStart = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--iPaddStart] = extra_c;
			return (write(1, &buffer[iPaddStart], i - iPaddStart) +
				write(1, &buffer[ind], length - (1 - iPaddStart)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsignd - Write an unsigned number.
 * @is_negative: A flag indicating if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: An array of characters.
 * @flags: Flags for formatting.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: The number of characters written.
 */
int write_unsignd(int is_negative, int ind,
	char buffer[], int flags, int width, int precision, int size)
{
	int iLength = BUFF_SIZE - ind - 1, i = 0;
	char iPadd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < iLength)
		iPadd = ' ';

	while (precision > iLength)
	{
		buffer[--ind] = '0';
		iLength++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		iPadd = '0';

	if (width > iLength)
	{
		for (i = 0; i < width - iLength; i++)
			buffer[i] = iPadd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], iLength) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], iLength));
		}
	}

	return (write(1, &buffer[ind], iLength));
}

/**
 * write_pointers - Write a memory address.
 * @buffer: An array of characters.
 * @ind: Index at which the number starts in the buffer.
 * @length: Length of the number.
 * @width: Width specifier.
 * @flags: Flags specifier.
 * @padd: The character representing padding.
 * @extra_c: The character representing an extra character.
 * @paddstart: Index at which padding should start.
 *
 * Return: The number of characters written.
 */
int write_pointers(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int paddstart)
{
	int j;

	if (width > length)
	{
		for (j = 3; j < width - length + 3; j++)
			buffer[j] = padd;
		buffer[j] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to the left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], j - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to the left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], j - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to the left of padd */
		{
			if (extra_c)
				buffer[--paddstart] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[paddstart], j - paddstart) +
				write(1, &buffer[ind], length - (1 - paddstart) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}