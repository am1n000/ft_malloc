/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:12:29 by ael-rhai          #+#    #+#             */
/*   Updated: 2021/11/11 14:05:11 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(long long i)
{
	int	a;

	a = 1;
	if (i < 0)
	{
		i *= -1;
		a = 2;
	}
	if (i >= 0 && i < 10)
		return (a);
	while (i > 9)
	{
		i = i / 10;
		a++;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long long	p;

	p = n;
	str = (char *)ft_calloc(ft_count(p) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = ft_count(p);
	str[i] = '\0';
	i--;
	if (p < 0)
		p *= -1;
	while (i >= 0)
	{
		str[i] = p % 10 + '0';
		p = p / 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
