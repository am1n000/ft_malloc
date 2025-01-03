/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:34:34 by ael-rhai          #+#    #+#             */
/*   Updated: 2025/01/02 21:57:48 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void    set_block(t_block **block, size_t size)
{
    (*block)->original_size = size;
    (*block)->data_size = size;
    (*block)->is_free = FALSE;
    (*block)->next = NULL;
    (*block)->prev = NULL;
}

void    divide_block(t_area **area, t_block **block, size_t size)
{
    //dividing a free block when the size of the new data is less than the_block's original data size
    t_block *divided_block;
    
    (*block)->is_free = FALSE;
    if (size == (*block)->data_size || (*block)->data_size < size + BLOCK_HEADER_SIZE + 1)
    {
        (*block)->data_size = size;
        return;
    }
    divided_block = *block + size;
    divided_block->data_size = (*block)->data_size - size - BLOCK_HEADER_SIZE;
    divided_block->original_size = divided_block->data_size;
    divided_block->is_free = TRUE;
    divided_block->next = (*block)->next;
    divided_block->prev = (*block);
    
    (*block)->data_size = size;
    (*block)->next = divided_block;
    (*area)->block_count++;
}

t_block    *place_tiny_small_block(size_t size, t_area_type area_type)
{
    t_area  *tmp_areas;
    t_block *block;
    t_block *new_block;
    
    tmp_areas = g_areas;

    while (tmp_areas)
    {
        if(tmp_areas->type == area_type)
        {
            block = ((t_block *)AREA_MOVE(tmp_areas));
            if(tmp_areas->block_count == 0) 
            {// if it's the first block on the area
                set_block(&block, size);
                tmp_areas->block_count++;
                tmp_areas->free_size -= size + BLOCK_HEADER_SIZE;
                return (block);
            }
            while (block)
            { //loop on the blocks
                if (block->is_free && size <= (size_t)block->original_size) 
                {//if a block is free and there is bigger divide it
                    divide_block(&tmp_areas, &block, size);
                    return (block);
                }
                if (block->next == NULL && size <= tmp_areas->free_size)
                {//if this block is the last and there is space in the area add new block
                    new_block = (t_block*)((char *)block + BLOCK_HEADER_SIZE + block->data_size);
                    block->original_size = block->data_size; //because we place the next block at the end of this block's data 
                    set_block(&new_block, size);
                    tmp_areas->block_count++;
                    new_block->prev = block;
                    block->next = new_block;
                    tmp_areas->free_size -= size + BLOCK_HEADER_SIZE;
                    return(new_block);
                }
                block = block->next;
            }
        }
        if (tmp_areas->next == NULL)
            return (add_new_area(size, area_type));
        tmp_areas = tmp_areas->next;
    }
    return (NULL);
}

void    *allocate_block(size_t size, t_area_type area_type)
{
    t_area  *tmp_areas;

    tmp_areas = g_areas;
    if (area_type != LARGE)
    {
        if (tmp_areas == NULL)
        {
            tmp_areas = create_area(size, area_type);
            if (!tmp_areas)
                return (NULL);
            g_areas = tmp_areas;
        }
		return (place_tiny_small_block(size, area_type));
    }
    else
        return(allocate_large(size));
    return (NULL);
}
