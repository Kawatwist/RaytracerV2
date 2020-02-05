/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/05 04:46:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point	find_dir(t_thread *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	return (ret);
}

int				start_thread(t_data *data)
{
	struct timespec	timeout;
	int				i;
	int				err;

	i = -1;
	load_modif(data, data->thread);
	while (++i < 4)
	{
		((t_thread *)data->thread)[i].percent = data->percent;
		((t_thread *)data->thread)[i].bounce = data->bounce;
		((t_thread *)data->thread)[i].len = (data->window.x * data->window.y) >> 2;
		((t_thread *)data->thread)[i].pos = ((t_thread *)data->thread)[i].len * i;
		((t_thread *)data->thread)[i].pxl = &(((unsigned char *)data->window.pxl)[(((t_thread *)data->thread)[i].len * i) << 2]);
		if ((err = pthread_create(&((t_thread*)data->thread)[i].thd, NULL, &thread_function, &((t_thread*)data->thread)[i])) != 0)
			return (err);
	}
	i = -1;
	while (i < 4)
	{
		timeout.tv_sec = 0;
		timeout.tv_nsec = 250;
		if (pthread_timedjoin_np(((t_thread *)data->thread)[i].thd, NULL, &timeout) == ETIMEDOUT)
		{
			if (SDL_QuitRequested())
				stop_execute("Quit Requested before Thread_join finished\n/!\\  Caution  /!\\\nThis will do leaks if thread is not stop correctly (pthread_cancel => free_data)\n", data);
		}
		else
		{
			data->obj.camera[data->obj.index[0]].pos.direction =
				normalize(find_dir(data->thread, data->window.x >> 1,
				data->window.y >> 1));
			i++;
		}
	}
	return (0);
}
