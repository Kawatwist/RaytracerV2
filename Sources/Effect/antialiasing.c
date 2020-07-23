/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:48:33 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/23 14:04:23 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point		find_dir(t_thread *data, float x, float y, int cam)
{
	t_point		ret;

	if (!data->obj.camera[data->obj.index[0]].mode || cam == 0)
	{
		ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
		ret =
		add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
		ret =
		add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
		ret =
		sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	}
	else
	{
		ret = veccpy(data->obj.camera[data->obj.index[0]].stereo->sc);
		ret =
		add_vec(ret,
		mult_vec2(data->obj.camera[data->obj.index[0]].stereo->x, x));
		ret =
		add_vec(ret,
		mult_vec2(data->obj.camera[data->obj.index[0]].stereo->y, y));
		ret =
		sub_vec(ret, data->obj.camera[data->obj.index[0]].stereo->pos.origin);
	}
	return (ret);
}

static t_vec		setup_ray(t_thread *data, float x, float y, int cam)
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

static int			uniformize_color(unsigned int curr_pixel[64], int max)
{
	unsigned long int	colors[4];
	int					i;

	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	colors[3] = 0;
	i = 0;
	while (i < max)
	{
		colors[0] += curr_pixel[i] % 256;
		colors[1] += (curr_pixel[i] >> 8) % 256;
		colors[2] += (curr_pixel[i] >> 16) % 256;
		colors[3] += (curr_pixel[i] >> 24) % 256;
		i++;
	}
	return (((colors[3] / max) << 24) + ((colors[2] / max) << 16) +
					((colors[1] / max) << 8) + (colors[0] / max));
}

unsigned int		send_aa_vr(t_thread *data, int x, int y, int curr)
{
	unsigned int color;

	if (curr % data->x < data->x / 2.0)
		color = send_ray(data, setup_ray(data,
					(x * 2.0) + (((rand() % 100) - 50) / 200.0),
					y + (((rand() % 100) - 50) / 200.0), 0), data->bounce, NULL);
	else
		color = send_ray(data, setup_ray(data,
					((x - (data->x / 2.0)) * 2.0) +
					(((rand() % 100) - 50) / 200.0),
					y + (((rand() % 100) - 50) / 200.0), 1), data->bounce, NULL);
	return (color);
}

void				aa_render(t_thread *data, int *x, int *y, int *curr)
{
	unsigned int	color[64];
	int				i;
	static	int		aa;

	aa = 1 << (data->flag.antialiasing * 2);
	*y = (*curr / data->x) + (data->pos / data->x);
	*x = *curr % data->x;
	i = -1;
	while (++i < aa)
	{
		if (data->obj.camera[data->obj.index[0]].mode != 2)
		{
			color[i] = send_ray(data, setup_ray(data,
				*x + (((rand() % 100) - 50) / 200.0),
				*y + (((rand() % 100) - 50) / 200.0), 0), data->bounce, NULL);
			if (data->obj.camera[data->obj.index[0]].mode == 1)
				color[i] = (send_ray(data, setup_ray(data,
				*x + (((rand() % 100) - 50) / 200.0),
				*y + (((rand() % 100) - 50) / 200.0), 1),
				data->bounce, NULL) & 0xFFFF) | (color[i] & 0xFF0000);
		}
		else
			color[i] = send_aa_vr(data, *x, *y, *curr);
	}
	((unsigned int *)data->pxl)[*curr] = uniformize_color(color, aa);
}
