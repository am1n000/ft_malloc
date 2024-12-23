/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:57:21 by ael-rhai          #+#    #+#             */
/*   Updated: 2024/12/22 18:00:45 by ael-rhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_area  *g_areas = NULL;
pthread_mutex_t  g_mutex = PTHREAD_MUTEX_INITIALIZER;
