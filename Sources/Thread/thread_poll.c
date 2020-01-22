/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_poll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:05:45 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 22:41:24 by lomasse          ###   ########.fr       */
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
		pthread_mutex_unlock(&data->mutex);
		printf("Poll Lock [%d]\n", i);
		((t_thread *)data->thread)[i].index = ((((t_thread *)data->thread)[i].x * ((t_thread *)data->thread)[i].y) / 4) * i;
		((t_thread *)data->thread)[i].len = ((data->window.x * data->window.y) / 4); // Chevauchement ? Need -1 ?
		((t_thread *)data->thread)[i].pxl = &(data->window.pxl[((t_thread *)data->thread)[i].index]);
		((t_thread *)data->thread)[i].bounce = data->bounce;
		printf("Poll Unlock\n");
		pthread_mutex_lock(&data->mutex);
	}
	i = -1;
	while (++i < 4)
		while (((t_thread *)data->thread)[i].len)
			pthread_cond_wait(&data->cond, &data->mutex);
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