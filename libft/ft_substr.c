/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:21:00 by ael-rhai          #+#    #+#             */
/*   Updated: 2021/11/15 17:09:35 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (0);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		substr = ft_strdup(&s[start]);
	else
	{
		substr = ft_calloc(len + 1, sizeof(char));
		if (!substr)
			return (NULL);
		ft_strlcpy(substr, &s[start], len + 1);
	}
	return (substr);
}
