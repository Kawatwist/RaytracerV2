/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_poll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:05:45 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 00:35:15 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

int		thread_poll(t_data *data)
{
	int				i;

	i = -1;
	while (++i < 4)
	{
		((t_thread *)data->thread)[i].index = ((((t_thread *)data->thread)[i].x * ((t_thread *)data->thread)[i].y) / 4) * i;
		((t_thread *)data->thread)[i].len = ((((t_thread *)data->thread)[i].x * ((t_thread *)data->thread)[i].y) / 4); // Chevauchement ? Need -1 ?
		((t_thread *)data->thread)[i].pxl = &(data->window.pxl[((t_thread *)data->thread)[i].index]);
		pthread_mutex_unlock(&((t_thread *)data->thread)[i].mutex);
		pthread_cond_signal(&((t_thread *)data->thread)[i].cond);
	}
	pthread_cond_wait(&((t_thread *)data->thread)[i].cond, &((t_thread *)data->thread)[0].mutex);
	pthread_mutex_unlock(&((t_thread *)data->thread)[0].mutex);
	pthread_cond_wait(&((t_thread *)data->thread)[i].cond, &((t_thread *)data->thread)[1].mutex);
	pthread_mutex_unlock(&((t_thread *)data->thread)[1].mutex);
	pthread_cond_wait(&((t_thread *)data->thread)[i].cond, &((t_thread *)data->thread)[2].mutex);
	pthread_mutex_unlock(&((t_thread *)data->thread)[2].mutex);
	pthread_cond_wait(&((t_thread *)data->thread)[i].cond, &((t_thread *)data->thread)[3].mutex);
	pthread_mutex_unlock(&((t_thread *)data->thread)[3].mutex);
	printf("============================= END =======================================\n");
	return (0);
}

/* 
**
**  Reset Thread
**  Check Thread 1, 2, 3,...
**  Store every return Value ! Dont need it
**  Wait Thread
**  Stop Them and return
**
*/