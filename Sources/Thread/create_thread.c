/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/01 17:52:58 by lomasse          ###   ########.fr       */
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

static int		start_thread4(t_data *data, int i)
{
	int err;

	((t_thread *)data->thread)[i].max_dist = data->max_dist;
	((t_thread *)data->thread)[i].percent = data->percent;
	((t_thread *)data->thread)[i].bounce = data->bounce;
	((t_thread *)data->thread)[i].index_thread = i;
	((t_thread *)data->thread)[i].len =
		(data->window.x * data->window.y) >> 2;
	((t_thread *)data->thread)[i].pos =
		((t_thread *)data->thread)[i].len * i;
	((t_thread *)data->thread)[i].pxl = data->window.pxl;
	if ((err = pthread_create(&((t_thread*)data->thread)[i].thd,
		NULL, &thread_function, &((t_thread*)data->thread)[i])) != 0)
		return (err);
	return (0);
}

static int		start_thread3(t_data *data, int *pos, Uint32 *time)
{
	if (!data->flag.screen)
	{
		if (!data->flag.time && SDL_GetTicks() - *time > 1000)
			data->flag.time = 1;
		if (SDL_QuitRequested())
			return (stop_execute("", &data));
		if (data->flag.first == 0 || data->flag.time)
		{
			loading_sc(data, *pos);
			*pos += 1;
			*pos > 34 ? *pos = 0 : 0;
		}
	}
	return (0);
}

static int		start_thread2(t_data *data, struct timespec *timeout,
	int *pos, Uint32 *time)
{
	int i;
	int e;

	i = 0;
	while (i < 4)
	{
		timeout->tv_sec = 0;
		timeout->tv_nsec = 0;
		if (pthread_timedjoin_np(((t_thread *)data->thread)[i].thd,
			NULL, timeout) == ETIMEDOUT)
		{
			if ((e = start_thread3(data, pos, time)) != 0)
				return (e);
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

int				start_thread(t_data *data)
{
	Uint32			time;
	struct timespec	timeout;
	int				err;
	int				i;
	static int		pos = 0;

	i = -1;
	load_modif(data, data->thread);
	light_variance(data, data->thread);
	while (++i < 4)
	{
		((t_thread *)data->thread)[i].percent = data->percent;
		if ((err = start_thread4(data, i)) != 0)
			return (err);
	}
	time = SDL_GetTicks();
	i = start_thread2(data, &timeout, &pos, &time);
	if (i)
		return (i);
	if (!data->flag.screen)
		SDL_RenderClear(data->window.rend);
	data->flag.first = 1;
	return (0);
}
