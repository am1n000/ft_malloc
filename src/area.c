/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:33:16 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/22 20:44:53 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"


void    *create_area(size_t size, t_area_type area_type)
{
    t_area			*area;
    size_t			allocation_size;
	struct rlimit   rpl;

    if (area_type == TINY)
        allocation_size = TINY_AREA_SIZE;
    else if (area_type == SMALL)
        allocation_size = SMALL_AREA_SIZE;
    else {
        allocation_size = get_large_size(size);
    }
	if(getrlimit(RLIMIT_DATA, &rpl) < 0)
		return (NULL);
	if (rpl.rlim_max < allocation_size)
        return (NULL);
	area = mmap(0, allocation_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
    if (area == MAP_FAILED)
        return (NULL);
    ft_bzero(area, PAGE_SIZE);
	area->block_count = 0;
	area->free_size = PAGE_SIZE - AREA_HEADER_SIZE;
	area->prev = NULL;
	area->next = g_areas;
	area->type = area_type;
    return (area);
}

t_block *   add_new_area(t_area **area, size_t size, t_area_type area_type)
{
        t_block *block;
        t_area  *tmp_areas;

        tmp_areas = create_area(size, area_type);
        if (!tmp_areas)
            return (NULL);
        block = ((t_block *)AREA_MOVE(tmp_areas));
        set_block(&block, size);
        tmp_areas->block_count++;
        tmp_areas->free_size -= size + BLOCK_HEADER_SIZE;
        (*area)->prev = tmp_areas;
        g_areas = tmp_areas;
        return (block);
        
}

int select_area_type(size_t size)
{
    if (size <= (size_t)TINY_BLOCK_SIZE) 
        return (TINY);
    if (size <= (size_t)SMALL_BLOCK_SIZE)  
        return (SMALL);
    return (LARGE);
}

void    print_area(t_area *area)
{
    if (area->type == TINY)
        ft_putstr_fd("TINY : ", 1);
    else if (area->type == SMALL)
        ft_putstr_fd("SMALL : ", 1);
    else
        ft_putstr_fd("LARGE : ", 1);
    print_num_base((size_t)area, 16, TRUE);
    write(1, "\n", 1);
}
