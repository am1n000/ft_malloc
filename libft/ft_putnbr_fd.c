/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:28:11 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/20 17:15:13 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	p;

	p = n;
	if (n < 0)
	{
		p = n * -1;
		write (fd, "-", 1);
	}
	if (p <= 9)
		ft_putchar_fd(p + '0', fd);
	if (p > 9)
	{
		ft_putnbr_fd(p / 10, fd);
		ft_putnbr_fd(p % 10, fd);
	}
}
