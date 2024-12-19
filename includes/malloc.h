/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:36:37 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/19 12:49:14 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include "../libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
								#include <stdio.h>

typedef struct				s_block
{
    size_t			size;
    int				is_free;
    struct s_block	*prev;
    struct s_block	*next;
}							t_block;

typedef struct				s_area
{
    struct s_area   *prev;
    struct s_area   *next;
    size_t			size;
    int				block_count;
	t_block			*blocks;
}							t_area;

extern t_area		*g_area;	

#define HEADER_SIZE sizeof(t_header); // to get the size of the header
#define HEADER_POINTER(ptr) ((char *)(ptr) - HEADER_SIZE); // to get the pointer to the header



# define TINY_AREA  (4 * getpagesize())
# define SMALL_AREA (10 * TINY_AREA)

# define TINY_BLOCK  128
# define SMALL_BLOCK 1024



# define BLOCK_HEADER_SIZE sizeof(t_block)

# define AREA_HEADER_SIZE sizeof(t_area)

#endif
