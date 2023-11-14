#include "main.h"
/**
 * print_with_format - Print an argument based on its type and format.
 * @fmt: The formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: An index.
 * @buffer: An array for handling printing.
 * @flags: Flags indicating special formatting.
 * @width: The width for formatting.
 * @precision: The precision specification.
 * @size: The size specifier.
 *
 * Return: 1 if successful, 2 if there was an issue.
 */
int print_with_format(const char *fmt, int *ind, va_list list, char buffer[],
                      int flags, int width, int precision, int size)
{
    int i, unknownLen = 0, printedChars = -1;
    fmt_t fmt_types[] = {
        {'c', printChar}, {'s', printString}, {'%', printPercent},
        {'i', printInteger}, {'d', printInteger}, {'b', printBinary},
        {'u', printUnsigned}, {'o', printOctal}, {'x', printHexadecimal},
        {'X', printHexUpper}, {'p', printPointer}, {'S', printNonPrintable},
        {'r', printReverse}, {'R', printRot13String}, {'\0', NULL}
    };

    for (i = 0; fmt_types[i].fmt != '\0'; i++)
        if (fmt[*ind] == fmt_types[i].fmt)
            return fmt_types[i].fn(list, buffer, flags, width, precision, size);

    if (fmt_types[i].fmt == '\0') {
        if (fmt[*ind] == '\0')
            return -1;
        unknownLen += write(1, "%%", 1);
        if (fmt[*ind - 1] == ' ')
            unknownLen += write(1, " ", 1);
        else if (width) {
            --(*ind);
            while (fmt[*ind] != ' ' && fmt[*ind] != '%')
                --(*ind);
            if (fmt[*ind] == ' ')
                --(*ind);
            return 1;
        }
        unknownLen += write(1, &fmt[*ind], 1);
        return unknownLen;
    }

    return printedChars;
}
/**
 * printChar - Print a character.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printChar(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char character = va_arg(args, int);

	return (write_char(character, buffer, flags, width, precision, size));
}

/**
 * printString - Print a string.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printString(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * printPercent - Print a percent sign.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printPercent(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * printInteger - Print an integer.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printInteger(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_numbers(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * printBinary - Print an unsigned number in binary.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printBinary(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, iSum;
	unsigned int a[32];
	int iCount;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(args, unsigned int);
	m = 2147483648U; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, iSum = 0, iCount = 0; i < 32; i++)
	{
		iSum += a[i];
		if (iSum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			iCount++;
		}
	}
	return (iCount);
}

/**
 * printUnsigned - Print an unsigned number.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printUnsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int iNum = va_arg(args, unsigned long int);

	iNum = convert_size_unsigned(iNum, size);

	if (iNum == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (iNum > 0)
	{
		buffer[i--] = (iNum % 10) + '0';
		iNum /= 10;
	}

	i++;

	return (write_unsignd(0, i, buffer, flags, width, precision, size));
}

/**
 * printOctal - Print an unsigned number in octal notation.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printOctal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int iNum = va_arg(args, unsigned long int);
	unsigned long int init_num = iNum;

	UNUSED(width);

	iNum = convert_size_unsigned(iNum, size);

	if (iNum == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (iNum > 0)
	{
		buffer[i--] = (iNum % 8) + '0';
		iNum /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsignd(0, i, buffer, flags, width, precision, size));
}

/**
 * printHexadecimal - Print an unsigned number in hexadecimal notation.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printHexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHex(args, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * printHexUpper - Print an unsigned number in uppercase hexadecimal notation.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printHexUpper(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHex(args, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * printHex - Print a hexadecimal number in lowercase or uppercase.
 * @args: List of arguments.
 * @map_to: Array of values to map the number to.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @flag_ch: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printHex(va_list args, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int index = BUFF_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsigned(number, size);

	if (number == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[index--] = map_to[number % 16];
		number /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[index--] = flag_ch;
		buffer[index--] = '0';
	}

	index++;

	return (write_unsignd(0, index, buffer, flags, width, precision, size));
}
/**
 * printPointer - Print the value of a pointer variable.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printPointer(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra = 0, padding = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addresses;
	char map_to[] = "0123456789abcdef";
	void *addresses = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);

	if (addresses == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addresses = (unsigned long)addresses;

	while (num_addresses > 0)
	{
		buffer[index--] = map_to[num_addresses % 16];
		num_addresses /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (flags & F_PLUS)
		extra = '+', length++;
	else if (flags & F_SPACE)
		extra = ' ', length++;

	index++;

	return (write_pointers(buffer, index, length,
		width, flags, padding, extra, padd_start));
}

/**
 * printNonPrintable - Print ASCII codes in hexadecimal of
 * non-printable characters.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printNonPrintable(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(args, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += hex_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * printReverse - Print a reversed string.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printReverse(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(args, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * printRot13String - Print a string in ROT13 encoding.
 * @args: List of arguments.
 * @buffer: Buffer array for printing.
 * @flags: Active formatting flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int printRot13String(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}