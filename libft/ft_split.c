/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:35:25 by ael-rhai          #+#    #+#             */
/*   Updated: 2021/11/20 11:28:04 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s && *s != c)
			i++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (i + 1);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	size_t	k;
	char	**str;

	if (!s)
		return (0);
	k = 0;
	str = (char **)ft_calloc(ft_count(s, c), sizeof(char *));
	if (!str)
		return (0);
	while (*s)
	{
		j = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			s++;
			j++;
		}
		if (*(s - 1) != c)
			str[k++] = ft_substr(s - j, 0, j);
	}
	str[k] = 0;
	return (str);
}
