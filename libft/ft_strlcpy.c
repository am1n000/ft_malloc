/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:58:30 by ael-rhai          #+#    #+#             */
/*   Updated: 2021/11/12 20:11:03 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	j = 0;
	if (dstsize == 0)
		return (i);
	while (*src && j < dstsize - 1)
	{
		*dst = *src;
		src++;
		dst++;
		j++;
	}
	*dst = 0;
	return (i);
}
