/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_poll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:05:45 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/23 22:19:10 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

// int		thread_poll(t_data *data)
// {
// 	int				i;
// 	int				curr;
// 	int				count;

// 	count = -1;
// 	curr = -1;
// 	usleep(10);
// 	while (count < 4)
// 	{
// 		i = -1;
// 		while ((++i < 4 && curr < data->window.y) || (curr >= data->window.y && count < 4))
// 		{
// 			if (!pthread_mutex_trylock(&data->mutex))
// 			{
// 				((t_thread *)data->thread)[i].bounce = data->bounce;
// 				((t_thread *)data->thread)[i].index = (curr * data->window.x);
// 				((t_thread *)data->thread)[i].len = data->window.x;
// 				((t_thread *)data->thread)[i].pxl = &(data->window.pxl[curr * data->window.x * 4]);
// 				pthread_mutex_unlock(&data->mutex);
// 				pthread_cond_signal(&data->cond);
// 				curr += 1;
// 				if (curr >= data->window.y)
// 					count += 1;
// 			}
// 			else
// 				count = 0;
// 		}
// 		usleep(10);
// 	}
// 	printf("============================= END =======================================\n");
// 	return (0);
// }

/* 
**
**  Reset Thread
**  Check Thread 1, 2, 3,...
**  Store every return Value ! Dont need it
**  Wait Thread
**  Stop Them and return
**
*/