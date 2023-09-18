#include "main.h"
/**
 * handle_print - Printing an argument based on the argument type
 * @fmt: arguments are printed in this formatted string
 * @list: the arguments list to be printed
 * @flags: calculating the active flags
 * @width: getting the width.
 * @precision: specifies the precision
 * @size: specifies the size
 * @ind: ind.
 * @buffer: The print is handled by this buffer array.
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int z, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (z = 0; fmt_types[z].fmt != '\0'; z++)
		if (fmt[*ind] == fmt_types[z].fmt)
			return (fmt_types[z].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[z].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
