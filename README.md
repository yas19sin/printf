# Project: 0x11. C - Printf

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Usage](#usage)
- [Authors](#authors)

## Description

In the realm of C programming, the `printf()` function plays a pivotal role in displaying diverse data types, encompassing characters, strings, floats, integers, octal, and hexadecimal values. This ALX-SE assigned project endeavors to replicate the core functionality of `printf()`, presenting a customized implementation of this renowned C function.

## Features

- Encompasses various conversion specifiers, such as `%c` for characters and `%s` for strings.
- Manages additional conversion specifiers like `%d` and `%i` for integers.
- Incorporates support for `%b` for binary representation, `%r` for string reversal, and `%R` for ROT13 encoding.
- Appropriately handles the `%%` specifier to print a literal '%' character.

## Usage

To employ this custom `printf()` function, adhere to these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/yas19sin/printf.git
   ```

2. Compile your code using the subsequent command:
   ```bash
   gcc -Wall -Werror -Wextra -pedantic *.c -o _printf
   ```
3. Integrate the "main.h" header file into your source code utilizing the _printf() function.
   ```c
   #include "main.h"

    /**
    * main - Entry point
    *
    * Return: Always 0
    */
    int main(void)
    {
        _printf("Let's attempt to printf a simple sentence.\n");
        return (0);
    }
   ```
## Team Members

- [Karim ElHagouchi](https://github.com/hagouchikarim)
- [Yassine Ennaour](https://github.com/yas19sin)