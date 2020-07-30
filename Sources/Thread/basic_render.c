/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 14:32:57 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/29 17:26:07 by lomasse          ###   ########.fr       */
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

static int		quality(t_thread *data, t_ipoint dir, int *curr, int color)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (data->flag.pixel * 2) + 1 && dir.x + i < data->x)
	{
		j = -1;
		while (++j < (data->flag.pixel * 2) +1 && dir.y + j < data->y)
		{
			if (dir.y + j < data->y && dir.x + i < data->x)
				((unsigned int *)data->pxl)[dir.z + i + (j * data->x)] = color;
		}
	}
	return (*curr + ((data->flag.pixel * 2) - 1));
}

static void     setup_send_ray(t_thread *data, t_ipoint dir)
{
	if (!data->obj.camera[data->obj.index[0]].mode || data->obj.camera[data->obj.index[0]].mode == 1)
		((unsigned int *)data->pxl)[dir.z] = send_ray(data, setup_ray(data, dir.x,
			dir.y, 0), data->bounce, NULL);
	if (data->obj.camera[data->obj.index[0]].mode == 1)
		((unsigned int *)data->pxl)[dir.z] = ((send_ray(data,
			setup_ray(data, dir.x, dir.y, 1), data->bounce, NULL) & 0xFFFF) +
				(((unsigned int *)data->pxl)[dir.z] & 0xFF0000));
	else if (data->obj.camera[data->obj.index[0]].mode == 2)
	{
		if (dir.x < data->x / 2.0)
			((unsigned int *)data->pxl)[dir.z] = send_ray(data,
			setup_ray(data, ((dir.x) * 2), dir.y, 0),
				data->bounce, NULL);
		else
			((unsigned int *)data->pxl)[dir.z] = send_ray(data,
			setup_ray(data, (dir.x - (data->x / 2)) * 2, dir.y, 1),
				data->bounce, NULL);
	}
}

void			basic_render(t_thread *data, int *curr)
{
	t_ipoint		dir;
	static int		color[4] = {0, 0, 0, 0};

	dir.y = (data->index_thread + ((*curr / data->x) * 4)) * ((data->flag.pixel * 2) + 1);
	dir.x = *curr % data->x;
	dir.z = (dir.y * data->x) + dir.x;
	if (dir.y >= data->y)
		return ;
	if ((!(dir.x % ((data->flag.pixel * 2) + 1))) && !(dir.y % ((data->flag.pixel * 2) + 1)))
	{
		setup_send_ray(data, dir);
		color[(int)data->index_thread] = ((unsigned int *)data->pxl)[dir.z];
	}
	else
		*curr = quality(data, dir, curr, color[(int)data->index_thread]);
}
