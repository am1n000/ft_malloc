/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 08:34:50 by ael-rhai          #+#    #+#             */
/*   Updated: 2025/01/03 09:26:31 by ael-rhai         ###   ########.fr       */
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

void    free_tiny_small_block(t_area **area, t_block **block, bool only_area_type)
{
    t_area  *tmp_area;
    t_block *tmp_block;
    
    tmp_area = *area;
    tmp_block = *block;
    if (tmp_area->block_count == 1)
        remove_area(area, block, only_area_type);
    else
    {
        if (tmp_block->next == NULL)
            remove_last_block(area, block);
        else
            free_block(area, block);
    }
}

t_area *find_area(void *ptr)
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
                return(tmp_areas);
            block = block->next;
        }
        tmp_areas = tmp_areas->next;
    }
    return (NULL);
}

void    start_free(void *ptr)
{
    t_area  *tmp_areas;
    t_area  *tmp_areas2;
    t_block *block;

    tmp_areas = find_area(ptr);
    if (!tmp_areas)
        return;
    block = (void *)ptr - 32;
    tmp_areas2 = g_areas;
    while (tmp_areas2)
    {
        if (tmp_areas2 != tmp_areas && tmp_areas2->type == tmp_areas->type)
        {
            if (tmp_areas->type != LARGE)
                free_tiny_small_block(&tmp_areas, &block, FALSE);
            else
                remove_area(&tmp_areas, &block, FALSE);
            return;
        }
        tmp_areas2 = tmp_areas2->next;
    }
    if (tmp_areas->type != LARGE)
        free_tiny_small_block(&tmp_areas, &block, TRUE);
    else
        remove_area(&tmp_areas, &block, TRUE);
    
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