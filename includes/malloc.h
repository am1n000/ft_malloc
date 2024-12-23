/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:36:37 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/22 20:39:40 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <stdbool.h>
# include <pthread.h>
# include "../libft/libft.h"

#define PAGE_SIZE getpagesize()

# define TINY_AREA_SIZE  (4 * PAGE_SIZE)
# define SMALL_AREA_SIZE (8 * TINY_AREA_SIZE)

# define TINY_BLOCK_SIZE  TINY_AREA_SIZE / 128
# define SMALL_BLOCK_SIZE SMALL_AREA_SIZE / 128

typedef enum    e_boolean{
    FALSE,
    TRUE
}               s_boolean;

typedef enum	e_area_type {
	TINY,
	SMALL,
	LARGE
}				t_area_type;

typedef struct				s_block
{
    size_t			data_size;
    bool			is_free;
    int             original_size;
    struct s_block	*prev;
    struct s_block	*next;
}							t_block;

typedef struct				s_area
{
    struct s_area   *prev;
    struct s_area   *next;
    size_t			free_size;
    int				block_count;
	t_area_type		type;	
}							t_area;


extern t_area           *g_areas;
extern pthread_mutex_t  g_mutex;



# define BLOCK_HEADER_SIZE sizeof(t_block)
# define AREA_HEADER_SIZE sizeof(t_area)

# define BLOCK_MOVE(start) ((char *)start + BLOCK_HEADER_SIZE)
# define AREA_MOVE(start) ((char *)start + AREA_HEADER_SIZE)


/*-----------------------  functions  --------------------------*/

int     select_area_type(size_t size);
void    *my_malloc(size_t size);
void    *my_realloc(void *ptr, size_t size);
void    my_free(void *ptr);
void    show_alloc_mem();
void	print_num_base(size_t nb, char base, bool prefix);
void    remove_area(t_area **area, t_block **block);
void    remove_last_block(t_area **area, t_block **block);
void    merge_previous_block(t_area **area, t_block **block);
void    merge_next_block(t_area **area, t_block **block);
void    *create_area(size_t size, t_area_type area_type);
void    set_block(t_block **block, size_t size);
void    divide_block(t_area **area, t_block **block, size_t size);
void    *allocate_block(size_t size, t_area_type area_type);
void    print_area(t_area *area);
size_t	get_large_size(size_t size);
t_block *place_tiny_small_block(size_t size, t_area_type area_type);
t_block *add_new_area(t_area **area, size_t size, t_area_type area_type);
t_block *allocate_large(size_t size);

#endif
