#include "main.h"

/**
 * print_buffer - function to Prints the contents of the buffer if it exist
 * @buffer: Array
 * @buff_ind: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

/**
 * _printf - finction to Printf function
 * @format: argument
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int flags, width, precision, size, buff_ind = 0;
	int i, pr = 0, printed_cha = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_cha++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = h_flags(format, &i);
			width = h_width(format, &i, list);
			precision = h_precision(format, &i, list);
			size = h_size(format, &i);
			++i;
			pr = h_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (pr == -1)
				return (-1);
			printed_cha += pr;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (printed_cha);
}
