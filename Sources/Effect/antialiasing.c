/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:48:33 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/30 18:05:17 by lomasse          ###   ########.fr       */
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

unsigned int		send_aa_vr(t_thread *data, int x, int y, int i)
{
	unsigned int	color;
	int				aa_side;

	aa_side = (int)sqrtf((1 << (data->flag.antialiasing * 2)));
	if (x < data->x / 2.0)
		color = send_ray(data, setup_ray(data,
				(x * 2.0) + ((1.0 / aa_side) * (i % aa_side)),
				y + ((1.0 / aa_side) * (i / aa_side)), 0), data->bounce, NULL);
	else
		color = send_ray(data, setup_ray(data,
					((x - (data->x / 2.0)) * 2.0) +
				((1.0 / aa_side) * (i % aa_side)),
				y + ((1.0 / aa_side) * (i / aa_side)), 1), data->bounce, NULL);
	return (color);
}

void				aa_render(t_thread *data, int *x, int *y, int *curr)
{
	unsigned int	color[64];
	int				i;
	int				aa;
	int				a;

	aa = 1 << (data->flag.antialiasing * 2);
	*y = (data->index_thread + ((*curr / data->x) * 4));
	*x = *curr % data->x;
	i = -1;
	a = (int)sqrtf(aa);
	while (++i < aa)
	{
		if (data->obj.camera[data->obj.index[0]].mode != 2)
		{
			color[i] = send_ray(data, setup_ray(data, *x + ((1.0 / a) * (i %
				a)), *y + ((1.0 / a) * (i / a)), 0), data->bounce, NULL);
			if (data->obj.camera[data->obj.index[0]].mode == 1)
				color[i] = (send_ray(data, setup_ray(data,
				*x + ((1.0 / a) * (i % a)), *y + ((1.0 / a) * (i / a)), 1),
				data->bounce, NULL) & CC) | (color[i] & CR);
		}
		else
			color[i] = send_aa_vr(data, *x, *y, i);
	}
	((Uint32 *)data->pxl)[(*y * data->x) + *x] = uniformize_color(color, aa);
}
