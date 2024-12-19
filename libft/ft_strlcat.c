/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 08:56:51 by ael-rhai          #+#    #+#             */
/*   Updated: 2021/11/20 15:04:06 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ldst;
	size_t	lsrc;
	size_t	i;

	lsrc = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (lsrc);
	ldst = ft_strlen(dst);
	if (dstsize < ldst)
		return (lsrc + dstsize);
	else
	{
		while (src[i] && i + ldst < dstsize - 1)
		{
			dst[i + ldst] = src[i];
			i++;
		}
		dst[i + ldst] = 0;
	}
	return (lsrc + ldst);
}
