/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:30:24 by ael-rhai          #+#    #+#             */
/*   Updated: 2025/01/03 09:01:21 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void    remove_area(t_area **area, t_block **block, bool only)
{
    t_area  *tmp_area;
    size_t  area_size;

    tmp_area = *area;
    if (tmp_area->type == TINY)
        area_size = TINY_AREA_SIZE;
    else if (tmp_area->type == SMALL)
        area_size = SMALL_AREA_SIZE;
    else
        area_size = get_large_size((*block)->data_size);
    
    if (only)//if it's the only area of it's type
    {
        tmp_area->free_size += AREA_HEADER_SIZE + (*block)->original_size;
        tmp_area->block_count--;
        return;
    }
    else if (tmp_area->next == NULL && tmp_area->prev) //if it's the last area
        tmp_area->prev->next = NULL;
    else if (tmp_area->prev == NULL && tmp_area->next) // if it's the first area
    {
        tmp_area->next->prev = NULL;
        g_areas = tmp_area->next;
    }
    else
    {
        tmp_area->prev->next = tmp_area->next;
        tmp_area->next->prev = tmp_area->prev;
    }
    munmap(tmp_area, area_size);
}

void    remove_last_block(t_area **area, t_block **block)
{
    t_area  *tmp_area;
    t_block *tmp_block;
    
    tmp_area = *area;
    tmp_block = *block;
    tmp_block->prev->next = NULL;
    tmp_area->free_size += AREA_HEADER_SIZE + tmp_block->data_size;
    tmp_area->block_count--;
}

void    merge_previous_block(t_area **area, t_block **block)
{
    t_block *tmp_block;
    
    tmp_block = *block;
    tmp_block->prev->next = tmp_block->next;
    tmp_block->prev->data_size += BLOCK_HEADER_SIZE + tmp_block->data_size;
    tmp_block->next->prev = tmp_block->prev;
    (*area)->block_count--;
    
}

void    merge_next_block(t_area **area, t_block **block)
{
    t_block *tmp_block;
    
    tmp_block = *block;
    tmp_block->next = tmp_block->next->next;
    tmp_block->data_size += BLOCK_HEADER_SIZE + tmp_block->next->data_size;
    tmp_block->next->next->prev = tmp_block;
    (*area)->block_count--;
}
