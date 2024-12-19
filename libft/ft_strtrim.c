/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:59:11 by ael-rhai          #+#    #+#             */
/*   Updated: 2021/11/19 14:10:57 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_startrim(const char *str, char const *needle)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (str[a] && needle[b])
	{
		if (str[a] == needle[b])
		{
			a++;
			b = -1;
		}
		b++;
	}
	return (a);
}

size_t	ft_endtrim(const char *str, char const *needle)
{
	size_t	a;
	size_t	b;

	a = ft_strlen(str) - 1;
	b = 0;
	while (a > 0 && needle[b])
	{
		if (str[a] == needle[b])
		{
			a--;
			b = -1;
		}
		b++;
	}
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	size_t	i;
	size_t	j;

	if (!s1)
		return (0);
	i = ft_startrim(s1, set);
	j = ft_endtrim(s1, set) + 1;
	if (i >= j)
	{
		strim = ft_calloc(1, 1);
		if (!strim)
			return (NULL);
		return (strim);
	}
	strim = ft_substr(s1, i, j - i);
	return (strim);
}
