/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:18:17 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/22 14:35:05 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"


size_t	get_large_size(size_t size)
{
	return((size + AREA_HEADER_SIZE + BLOCK_HEADER_SIZE)
			+ (PAGE_SIZE-1)) & ~(PAGE_SIZE-1);
}

void	print_num_base(size_t nb, char base, bool prefix)
{
	char	*str;

	str = "0123456789ABCDEF";
	if (nb / base)
		print_num_base(nb / base, base, prefix);
	else
	{
		if (prefix)
			ft_putstr_fd("0x", 1);
	}
	write(1, &str[nb % base], 1);
}