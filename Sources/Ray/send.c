/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:30 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/13 20:10:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	t_point	find_dir(t_data *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[0].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[0].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[0].y, y));
	ret = sub_vec(ret, data->obj.camera[0].pos.origin);
	return (ret);
}

static void		low_quality(t_data *data, int *x, int *y)
{
	int		w;
	int		pxl;

	w = 0;
	pxl = 0;
	while (w < data->window.x)
	{
		pxl = 0;
		while (pxl < ((data->flag.pixel) * 2))
		{
			((unsigned int *)data->window.pxl)[(*x) +
					((*y + pxl) * data->window.x) + w] =
				((unsigned int *)data->window.pxl)[*x +
						((*y - 1) * data->window.x) + w];
			pxl++;
		}
		w++;
	}
	(*y) += (data->flag.pixel);
}

static void		low_pixel_x(t_data *data, int *x, int y)
{
	while (*x % (data->flag.pixel + 1))
	{
		((unsigned int *)data->window.pxl)[*x + 1 +
			(y * data->window.x)] =
			((unsigned int *)data->window.pxl)
			[*x + (y * data->window.x)];
		*x += 1;
	}
}

static void		setup_ray(t_data *data, int x, int y)
{
	data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
	data->ray.direction = normalize(find_dir(data, x, y));
}

int				start_ray(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->window.y)
	{
		x = -1;
		while (++x < data->window.x)
		{
			setup_ray(data, x, y);
			((unsigned int *)data->window.pxl)[x + (y * data->window.x)] =
					send_ray(data, data->ray, data->bounce);
			low_pixel_x(data, &x, y);
		}
		data->flag.pixel ? low_quality(data, &x, &y) : 0;
	}
	data->obj.camera[data->obj.index[0]].pos.direction =
		normalize(find_dir(data, data->window.x >> 1,
		data->window.y >> 1));
	return (0);
}
