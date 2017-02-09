/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 16:01:26 by exam              #+#    #+#             */
/*   Updated: 2017/02/02 16:51:55 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_opp
{
	char	ch;
	int (*f)(int, int);
}				t_opp;

int		ft_add(int a, int b) {return (a+b);}
int		ft_sub(int a, int b) {return (a-b);}
int		ft_mul(int a, int b) {return (a*b);}
int		ft_div(int a, int b) {return (a/b);}
int		ft_mod(int a, int b) {return (a%b);}

t_opp *make_tab(void)
{
	t_opp *var = malloc(sizeof(t_opp)*5);

	var[0].ch = '+'; var[0].f = &ft_add;
	var[1].ch = '-'; var[1].f = &ft_sub;
	var[2].ch = '*'; var[2].f = &ft_mul;
	var[3].ch = '/'; var[3].f = &ft_div;
	var[4].ch = '%'; var[4].f = &ft_mod;
	return (var);
}

int ft_isnum(char ch) {return(ch >= '0' && ch <= '9');}
int ft_isopp(char ch) {return(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');}

char *ft_strcpy(char *s1, char *s2)
{
	int i = 0;

	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}

int rpn_calc(char *str, int *poz, t_opp *tab, int *error)
{
	int i, op1, op2, j;

	i = *poz - 2;
	while (str[i-1] != ' ' && i > 0)
		i--;
	if (i == 0)
	{
		*error = 1;
		return (0);
	}
	if (ft_isnum(str[i]) || (str[i] == '-' && str[i+1] != ' '))
		op2 = atoi(&str[i]);
	else
		op2 = rpn_calc(str, &i, tab, error);

	i -= 2;
	
	while (str[i-1] != ' ' && i > 0)
		i--;
	if (ft_isnum(str[i]) || (str[i] == '-' && str[i+1] != ' '))
		op1 = atoi(&str[i]);
	else
		op1 = rpn_calc(str, &i, tab, error);

	if (*error)
		return (0);
	j = 0;
	while (j != 5)
	{
		if (tab[j].ch == str[*poz])
		{
			if ((tab[j].ch == '/' || tab[j].ch == '%') && op2 == 0)
			{
				*error = 1;
				return (0);
			}
			*poz = i;
			return (tab[j].f(op1, op2));
		}
		j++;
	}
	return (0);
}

int ctrl(char *s)
{
	int i = 0, k = 0;

	while (s[i])
	{
		if (!(ft_isnum(s[i]) || ft_isopp(s[i]) || s[i] == ' '))
			return (1);
		else if (ft_isnum(s[i]))
			k++;
		i++;
	}
	!k ? return (1) : return (0);
}

int main(int ac, char **av)
{
	int poz=0, error=0, rez;

	if (ac == 2 && *av != '\0')
	{
		if (!ctrl(av[1]))
		{
			while (av[1][poz+1] != '\0' && (av[1][poz] == ' ' ||
				(ft_isnum(av[1][poz]) && (ft_isnum(av[1][poz+1])|| av[1][poz+1] == ' ' || !av[1][poz+1]))
				|| (ft_isopp(av[1][poz]) && (!av[1][poz+1] || av[1][poz+1] == ' ' ||
					(av[1][poz] == '-'	&& ft_isnum(av[1][poz+1]))))))
				poz++;
			while (av[1][poz+1] != '\0')
				poz++;
			if (ft_isopp(av[1][poz]))
			{
				rez = rpn_calc(av[1], &poz, make_tab(), &error);
				if(!error && !poz)
				{
					printf("%d\n", rez);
					return (0);
				}
			}
		}
	}
	printf("Error\n");
	return (0);
}
