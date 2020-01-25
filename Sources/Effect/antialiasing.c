/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:48:33 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/25 18:19:37 by lomasse          ###   ########.fr       */
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

static void		uniformize_color(unsigned int curr_pixel[16], int max)
{
	unsigned int	colors[4];
	int				i;

	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	colors[3] = 0;
	i = 0;
	while (i < max * max)
	{
		colors[0] += curr_pixel[i] % 256;
		colors[1] += (curr_pixel[i] >> 8) % 256;
		colors[2] += (curr_pixel[i] >> 16) % 256;
		colors[3] += (curr_pixel[i] >> 24) % 256;
		i++;
	}
	curr_pixel[0] = ((colors[3] / (max * max)) << 24) + ((colors[2] / (max * max)) << 16) +
					((colors[1] / (max * max)) << 8) + (colors[0] / (max * max));
}

static void		extra_samples(t_data *data, t_vec next_ray_x, t_vec next_ray_y, unsigned int curr_pixel[16])
{
	int		x;
	int		y;
	int 	tmp;
	t_vec	curr_ray;

	tmp = data->flag.antialiasing + 1; //niveau de AA de 0 a 3; (niveau + 1)^2 samples
	y = -1;
	curr_ray.origin = data->ray.origin;
	while (++y < tmp)
	{
		x = -1;
		while (++x < tmp)
		{
			curr_ray.direction = add_vec(data->ray.direction,   //calcul rayon intermediaire
				add_vec(mult_vec2(div_vec2(sub_vec(next_ray_x.direction,
					data->ray.direction), -tmp), x),
				mult_vec2(div_vec2(sub_vec(next_ray_y.direction,
				data->ray.direction), -tmp), y)));
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

	if ((data->flag.antialiasing & 0b11) > 0)
	{
		setup_ray(data, x + 1, y);
		next_ray_x = data->ray; //next ray on X axis
		setup_ray(data, x, y + 1);
		next_ray_y = data->ray; //next ray on y axis
		setup_ray(data, x, y);
		extra_samples(data, next_ray_x, next_ray_y, curr_pixel);
		((unsigned int *)data->window.pxl)[x + (y * data->window.x)] =
			curr_pixel[0];
	}
	else
	{
		setup_ray(data, x, y);
		((unsigned int *)data->window.pxl)[x + (y * data->window.x)] =
					send_ray(data, data->ray, data->bounce);
	}
}
