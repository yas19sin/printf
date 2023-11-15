#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Format specification structure.
 *
 * @fmt: The format specifier.
 * @fn: The associated function pointer.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Format specification type.
 *
 * @fmt: The format specifier.
 * @fn: The associated function pointer.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
void buffer_print(char buff[], int *buff_index);
int append_to_buffer(char buff[], int *buff_index, const char *str);

int extract_flags(const char *format, int *i);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);

int is_printable(char c);
int is_digit(char c);
int hex_code(char asciiCode, char buffer[], int i);
long int convert_size_number(long int num, int size);
long int convert_size_unsigned(unsigned long int num, int size);

int write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_numbers(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c);
int write_unsignd(int is_negative, int ind,
	char buffer[], int flags, int width, int precision, int size);
int write_pointers(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int paddstart);

int print_with_format(const char *fmt, int *ind, va_list list, char buffer[],
					  int flags, int width, int precision, int size);
int printChar(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printString(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printPercent(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printInteger(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printBinary(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printUnsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printOctal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printHexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printHexUpper(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printHex(va_list args, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size);
int printPointer(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printNonPrintable(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printReverse(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int printRot13String(va_list args, char buffer[],
	int flags, int width, int precision, int size);

#endif /* MAIN_H */