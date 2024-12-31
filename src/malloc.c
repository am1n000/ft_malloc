/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:14:41 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/31 13:55:24 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block    *allocate_large(size_t size)
{
    t_block *block;
    t_area *tmp_areas;
    
    tmp_areas = g_areas;
    g_areas = create_area(size, LARGE);
    if (!g_areas)
        return (NULL);
    if (tmp_areas)
        tmp_areas->prev = g_areas;
    block = ((t_block *)AREA_MOVE(g_areas));
    set_block(&block, size);
    return (block);
}

void    *allocate(size_t  size)
{
    void            *block;
    t_area_type		type;
    type = select_area_type(size);
    block = allocate_block(size, type);
    if (block)
        return (block + BLOCK_HEADER_SIZE);
    return (NULL);
}

void *start_malloc(size_t size)
{
    void* ptr;
    
    if (size == 0)
        return (NULL);
    size = (size + 15) & ~15; //for the alignment
    ptr = allocate(size);
    return (ptr);
}

void    *malloc(size_t size)
{
    void* ptr;
    
    pthread_mutex_lock(&g_mutex);
    ptr = start_malloc(size);
    pthread_mutex_unlock(&g_mutex);
    return (ptr);    
}



