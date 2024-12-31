/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:50:38 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/31 13:55:38 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block *find_pointer(void *ptr)
{
    t_area  *tmp_areas;
    t_block *block;

    tmp_areas = g_areas;
    while (tmp_areas)
    {

        block = (t_block *)(AREA_MOVE(tmp_areas));
        while (block)
        {
            if (ptr == (void *)BLOCK_MOVE(block))
                return(block);
            block = block->next;
        }
        tmp_areas = tmp_areas->next;
    }
    return (NULL);
}

void    *start_realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
    block = find_pointer(ptr);
	if (block == NULL)
		return (NULL);
	if (size == block->data_size)
		return (ptr);
	new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, block->data_size > size ? size : block->data_size);
	free(ptr);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	
	pthread_mutex_lock(&g_mutex);
	new_ptr = start_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}