/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:16:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/23 22:19:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void	*thread_function(void *arg)
{
	t_thread 		*data;
	// Uint32			color;

	data = arg;
	while (--data->len)
	{
		((Uint32 *)data->pxl)[data->len] = 0xFFFFFFFF;
	}
	return (arg);
}
