/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:18:33 by exam              #+#    #+#             */
/*   Updated: 2016/12/15 17:01:16 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*parse(char *s)
{
	int i,j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '(' || s[i] == ')' || s[i] == '[' ||
				s[i] == ']' || s[i] == '{' || s[i] == '}')
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
	return (s);
}

int		br(char *s)
{
	int i = 0;

	while (s[i])
	{
		if ((s[i] == '(' && s[i+1] == ')') || (s[i] == '[' && s[i+1] == ']')
			|| (s[i] == '{' && s[i+1] == '}'))
		{
			if (s[i+2] == '\0')
			{
				s[i+1] = '\0';
				s[i] = '\0';
			}
			else while (s[i+2])
			{
				s[i] = s[i+2];
				i++;
				if (s[i+2] == '\0')
				{
					s[i+1] = '\0';
					s[i] = '\0';
				}
			}
			i = -1;
		}
		i++;
	}
	if (s[0])
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	int i = 1;

	if (ac > 1)
	{
		while (av[i])
		{
			if (br(parse(av[i])))
				write(1, "OK\n", 3);
			else
				write(1, "Error\n", 6);
			i++;
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}
