/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 00:59:11 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/29 13:49:40 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void		check_mutex(t_data *data)
{
	int		i;

	i = -1;
	if (key_check(data, SDL_SCANCODE_G))
	{
		while (++i < 4)
		{
			while (pthread_mutex_trylock(&((t_thread *)
			(data)->thread)[i].mutex))
				;
			((t_thread *)(data)->thread)[i].signal = SIGTSTP;
			pthread_mutex_unlock(&((t_thread *)(data)->thread)[i].mutex);
		}
	}
}
