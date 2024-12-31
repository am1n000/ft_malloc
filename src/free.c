/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 08:34:50 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/31 13:55:17 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void    free_block(t_area **area, t_block **block)
{
    t_block *tmp_block;
    
    tmp_block = *block;
    tmp_block->is_free = 1;
    if (tmp_block->prev && tmp_block->prev->is_free)
    {
        merge_previous_block(area, block);
        if (tmp_block->next->is_free)
            merge_next_block(area, &tmp_block->prev);
    }
    else if(tmp_block->next->is_free)
            merge_next_block(area, &tmp_block->prev);
}

void    free_tiny_small_block(t_area **area, t_block **block)
{
    t_area  *tmp_area;
    t_block *tmp_block;
    
    tmp_area = *area;
    tmp_block = *block;
    if (tmp_area->block_count == 1)
        remove_area(area, block);
    else
    {
        if (tmp_block->next == NULL)
            remove_last_block(area, block);
        else
            free_block(area, block);
    }
}

void    start_free(void *ptr)
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
            {
                if (tmp_areas->type != LARGE)
                    free_tiny_small_block(&tmp_areas, &block);
                else
                    remove_area(&tmp_areas, &block);
                return;
            }
            block = block->next;
        }
        tmp_areas = tmp_areas->next;
    }
}

void    free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
	pthread_mutex_lock(&g_mutex);
    start_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}