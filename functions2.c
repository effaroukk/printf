#include "main.h"

/**
 * print_pointer - Printing a pointer variable
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  Calculating the active flags
 * @width: get width
 * @precision: Precision specs
 * @size: specifing the size
 * Return: Number of chars to be printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - Printing the ascii codes in non printable hexa chars
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  Calculating the active flags
 * @width: get width
 * @precision: Precision specs
 * @size: specifing the size
 * Return: Number of chars to be printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int z = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[z] != '\0')
	{
		if (is_printable(str[z]))
			buffer[z + offset] = str[z];
		else
			offset += append_hexa_code(str[z], buffer, z + offset);

		z++;
	}

	buffer[z + offset] = '\0';

	return (write(1, buffer, z + offset));
}


/**
 * print_reverse - Printing the reverse string.
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  Calculating the active flags
 * @width: get width
 * @precision: Precision specifs
 * @size: specifing the size
 * Return: Numbers of chars to be printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int x, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (x = 0; str[x]; x++)
		;

	for (x = x - 1; x >= 0; x--)
	{
		char z = str[x];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Printing  rot13
 * @types: arguments list
 * @buffer: Buffer array
 * @flags:  Calculating the active flags
 * @width: get width
 * @precision: Precision specs
 * @size: specifing the size
 * Return: Numbers of chars to be printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int z, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (z = 0; str[z]; z++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[z])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[z];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

