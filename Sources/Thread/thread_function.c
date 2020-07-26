/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:16:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/26 13:49:23 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point		find_dir(t_thread *data, int x, int y, int cam)
{
	t_point		ret;

	if (!data->obj.camera[data->obj.index[0]].mode || cam == 0)
	{
		ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
		ret = add_vec(ret,
			mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
		ret = add_vec(ret,
			mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
		ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	}
	else
	{
		ret = veccpy(data->obj.camera[data->obj.index[0]].stereo->sc);
		ret = add_vec(ret,
			mult_vec2(data->obj.camera[data->obj.index[0]].stereo->x, x));
		ret = add_vec(ret,
			mult_vec2(data->obj.camera[data->obj.index[0]].stereo->y, y));
		ret = sub_vec(ret,
			data->obj.camera[data->obj.index[0]].stereo->pos.origin);
	}
	return (ret);
}

static t_vec		setup_ray(t_thread *data, int x, int y, int cam)
{
	if (cam == 0)
		data->ray.origin =
			veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
	else
		data->ray.origin =
			veccpy(data->obj.camera[data->obj.index[0]].stereo->pos.origin);
	data->ray.direction = normalize(find_dir(data, x, y, cam));
	return (data->ray);
}

static void			quality(t_thread *data, int *x, int *y, int *curr)
{
	while ((*x % ((data->flag.pixel * 2) + 1) || (*y % ((data->flag.pixel * 2)
			+ 1))) && *curr < data->len && *y == (*curr / data->x) +
			(data->pos / data->x))
	{
		if (*curr < data->x * ((data->flag.pixel * 2) + 1) || *y < (*y %
			((data->flag.pixel * 2) + 1)))
			((unsigned int *)data->pxl)[*curr] = ((unsigned int *)data->pxl)
				[*x - (*x % ((data->flag.pixel * 2) + 1))];
		else
			((unsigned int *)data->pxl)[*curr] = ((unsigned int *)data->pxl)
				[*curr - (*x % ((data->flag.pixel * 2) + 1) + ((*y %
					((data->flag.pixel * 2) + 1) * data->x)))];
		if (*x % (data->flag.pixel * 2) + 1)
			*curr += 1;
		else
			break ;
		*x = *curr % data->x;
	}
	*curr -= 1;
}

static void			basic_render(t_thread *data, int *x, int *y, int *curr)
{
	*y = (*curr / data->x) + (data->pos / data->x);
	*x = *curr % data->x;
	if (*curr < data->x || (!(*x % ((data->flag.pixel * 2) + 1)) && !(*y %
		((data->flag.pixel * 2) + 1))))
	{
		((unsigned int *)data->pxl)[*curr] = send_ray(data, setup_ray(data, *x,
				*y, 0), data->bounce, NULL);
		if (data->obj.camera[data->obj.index[0]].mode == 1)
			((unsigned int *)data->pxl)[*curr] = ((send_ray(data,
				setup_ray(data, *x, *y, 1), data->bounce, NULL) & 0xFFFF) +
					(((unsigned int *)data->pxl)[*curr] & 0xFF0000));
		else if (data->obj.camera[data->obj.index[0]].mode == 2)
		{
			if (*curr % data->x < data->x / 2.0)
				((unsigned int *)data->pxl)[*curr] = send_ray(data,
					setup_ray(data, ((*x) * 2), *y, 0), data->bounce, NULL);
			else
				((unsigned int *)data->pxl)[*curr] = send_ray(data,
				setup_ray(data, (*x - (data->x / 2) * 2), *y, 1),
					data->bounce, NULL);
		}
	}
	else
		quality(data, x, y, curr);
}

void				*thread_function(void *arg)
{
	t_thread		*data;
	int				x;
	int				y;
	int				curr;

	data = arg;
	curr = -1;
	data->signal = THREAD_ALIVE;
	while (++curr < data->len)
	{
		data->current = curr;
		if (!data->flag.screen && quitrequested(data) == THREAD_SIG)
			pthread_exit(NULL);
		if (data->flag.antialiasing == 0)
			basic_render(data, &x, &y, &curr);
		else
			aa_render(data, &x, &y, &curr);
		if (!(curr % 1000) && data->flag.time)
			SDL_Delay(2);
	}
	data->signal = NOTHREAD;
	return (arg);
}
