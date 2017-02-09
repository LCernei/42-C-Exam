/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:02:15 by exam              #+#    #+#             */
/*   Updated: 2016/12/15 16:15:50 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	rec(long n, int base, char *str, int *i)
{
	if (n == 0)
		return ;
	rec(n / base, base, str, i);
	str[(*i)++] = "0123456789ABCDEF"[n % base * (1 - 2 * (n < 0))];
}

char	*ft_itoa_base(int value, int base)
{
	char	*str = malloc(sizeof(char) * 64);
	int		i = 0;

	if (value == 0)
		str[i++] = '0';
	if (value < 0 && base == 10)
		str[i++] = '-';
	rec(value, base, str, &i);
	str[i] = '\0';
	return (str);
}
