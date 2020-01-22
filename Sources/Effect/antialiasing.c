/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:48:33 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/22 16:57:47 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	t_point	find_dir(t_data *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	return (ret);
}

static void		setup_ray(t_data *data, int x, int y)
{
	data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
	data->ray.direction = normalize(find_dir(data, x, y));
}

static void		uniformize_color(unsigned int *curr_pixel, int max)
{
	unsigned int	colors[3];
	int				i;
	int				j;

	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	i = -1;
	while (i++ < max)
	{
		j = -1;
		while(j++ < max)
		{
			colors[0] += curr_pixel[i + j * max] % 256;
			colors[1] += (curr_pixel[i + j * max] >> 8) % 256;
			colors[2] += (curr_pixel[i + j * max] >> 16) % 256;
		}
	}
	curr_pixel[0] = (255 << 24) + ((colors[2] / (max * max)) << 16) +
					((colors[1] / (max * max)) << 8) + (colors[0] / (max * max));
}

static void		extra_samples(t_data *data, t_vec next_ray_x, t_vec next_ray_y, unsigned int curr_pixel[16])
{
	int		x;
	int		y;
	int 	tmp;
	t_vec	curr_ray;

	tmp = data->flag.antialiasing + 1;
	y = -1;
	while (y++ < data->flag.antialiasing + 1)
	{
		x = -1;
		while (x++ < data->flag.antialiasing + 1)
		{
			curr_ray.direction = add_vec(data->ray.direction,   //calcul rayon intermediaire
				add_vec(mult_vec2(div_vec2(sub_vec(next_ray_x.direction,
					data->ray.direction), -tmp), x),
				mult_vec2(div_vec2(sub_vec(next_ray_y.direction,
				data->ray.direction), -tmp), y)));
			if (x + (y * tmp) != 0)
				curr_pixel[x + (y * tmp)] = send_ray(data, curr_ray, data->bounce);
		}
	}
	uniformize_color(curr_pixel, tmp);
}

void	super_sample(t_data *data, int x, int y)
{
	t_vec			next_ray_x;
	t_vec			next_ray_y;
	unsigned int 	curr_pixel[16];

	setup_ray(data, x + 1, y);
	next_ray_x = data->ray;
	setup_ray(data, x, y + 1);
	next_ray_y = data->ray;
	setup_ray(data, x, y);
	curr_pixel[0] = send_ray(data, data->ray, data->bounce);
	extra_samples(data, next_ray_x, next_ray_y, curr_pixel);
	((unsigned int *)data->window.pxl)[x + (y * data->window.x)] =
			curr_pixel[0];
}
