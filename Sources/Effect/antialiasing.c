/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:48:33 by cbilga            #+#    #+#             */
/*   Updated: 2020/02/17 12:00:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point		find_dir(t_thread *data, float x, float y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	return (ret);
}

static t_vec		setup_ray(t_thread *data, float x, float y)
{
	data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
	data->ray.direction = normalize(find_dir(data, x, y));
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
		color[i] = send_ray(data, setup_ray(data,
			*x + (((rand() % 100) - 50) / 100.0),
			*y + (((rand() % 100) - 50) / 100.0)), data->bounce);
	((unsigned int *)data->pxl)[*curr] =
		uniformize_color(color, aa);
}
