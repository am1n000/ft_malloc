/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:41:55 by ael-rhai          #+#    #+#             */
/*   Updated: 2021/11/12 19:50:08 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str1;
	char	*str2;
	size_t	i;

	i = 0;
	str1 = (char *)dst;
	str2 = (char *)src;
	if (!str1 && !str2)
		return (0);
	if (str1 > str2)
	{
		while (i < len--)
			str1[len] = str2[len];
	}
	else
	{
		while (len--)
			*str1++ = *str2++;
	}
	return (dst);
}
