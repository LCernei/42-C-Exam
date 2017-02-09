/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:02:32 by exam              #+#    #+#             */
/*   Updated: 2017/02/09 17:18:24 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void putchar(char c)
{
	write(1, &c, 1);
}

static void print_printable(const char *mem, size_t n)
{
	while (n > 0)
	{
		if (*mem >= ' ' && *mem <= '-')
			putchar(*mem);
		else
			putchar('.');
		mem++;
		n--;
	}
}

static void put_hex(unsigned char c)
{
	putchar("0123456789abcdef"[c / 16]);
	putchar("0123456789abcdef"[c % 16]);
}

static void print_hex(const char *mem, size_t n)
{
	unsigned int i = 0;
	int chars_printed = 0;
	while (i < n)
	{
		put_hex(mem[i]);
		if (i % 2 == 1)
		{
			putchar(' ');
			chars_printed +=1;
		}
		i++;
		chars_printed += 2;
	}
	while (chars_printed < 40)
	{
		putchar(' ');
		chars_printed +=1;
	}
}

void	print_memory(const void *addr, size_t size)
{
	const char *mem = addr;
	while (size >= 16)
	{
		print_hex(mem, 16);
		print_printable(mem, 16);
		putchar('\n');
		mem += 16;
		size -= 16;
	}
	if (size > 0)
	{
		print_hex(mem, size);
		print_printable(mem, size);
		putchar('\n');
	}
}
