/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 22:33:49 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/22 20:37:04 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void    print_block(t_block *block)
{
    print_num_base((size_t)block, 16, 1);
    ft_putstr_fd(" - ", 1);
    print_num_base((size_t)((char *)block + block->data_size), 16, 1);
    ft_putstr_fd(" : ", 1);
    print_num_base(block->data_size, 10, 0);
    ft_putstr_fd(" bytes\n", 1);
    
    
}

void    print_total(size_t total)
{
    ft_putstr_fd("Total : ", 1);
    print_num_base(total, 10, 0);
    ft_putstr_fd(" bytes\n", 1);
}

t_area  *get_first_area()
{
    t_area *tmp_areas;

    tmp_areas = g_areas;
    while (tmp_areas->next)
    {
        tmp_areas = tmp_areas->next;
    }
    return (tmp_areas);
}

void start_show_mem()
{
    t_area  *tmp_areas;
    t_block *block;
    size_t  total;

    total = 0;
    tmp_areas = get_first_area();
    while (tmp_areas)
    {
        print_area(tmp_areas);
        block = (t_block *)(AREA_MOVE(tmp_areas));
        while (block)
        {
            if (!block->is_free)
            {
                print_block(block);
                total += block->data_size;
            }
            block = block->next;
        }
        tmp_areas = tmp_areas->prev;
    }
    print_total(total);
}

void show_alloc_mem()
{
    pthread_mutex_lock(&g_mutex);
    start_show_mem();
    pthread_mutex_unlock(&g_mutex);
}

