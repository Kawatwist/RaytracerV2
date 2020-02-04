/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:48:33 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/28 19:41:00 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point	find_dir(t_thread *data, float x, float y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	return (ret);
}

static t_vec	setup_ray(t_thread *data, float x, float y)
{
	data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
	data->ray.direction = normalize(find_dir(data, x, y));
    return (data->ray);
}

static int		uniformize_color(unsigned int curr_pixel[16], int max)
{
	unsigned int	colors[4];
	int				i;

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

// static void		extra_samples(t_data *data, t_vec next_ray_x, t_vec next_ray_y, unsigned int curr_pixel[16])
// {
// 	int		x;
// 	int		y;
// 	int 	tmp;
// 	t_vec	curr_ray;

// 	tmp = data->flag.antialiasing + 1;
// 	y = -1;
// 	while (y++ < data->flag.antialiasing + 1)
// 	{
// 		x = -1;
// 		while (x++ < data->flag.antialiasing + 1)
// 		{
// 			curr_ray.direction = add_vec(data->ray.direction,   //calcul rayon intermediaire
// 				add_vec(mult_vec2(div_vec2(sub_vec(next_ray_x.direction,
// 					data->ray.direction), -tmp), x),
// 				mult_vec2(div_vec2(sub_vec(next_ray_y.direction,
// 				data->ray.direction), -tmp), y)));
// 			if (x + (y * tmp) != 0)
// 				curr_pixel[x + (y * tmp)] = send_ray(data, curr_ray, data->bounce);
// 		}
// 	}
// 	uniformize_color(curr_pixel, tmp);
// }

// void	super_sample(t_data *data, int x, int y)
// {
// 	t_vec			next_ray_x;
// 	t_vec			next_ray_y;
// 	unsigned int 	curr_pixel[16];

// 	setup_ray(data, x + 1, y);
// 	next_ray_x = data->ray;
// 	setup_ray(data, x, y + 1);
// 	next_ray_y = data->ray;
// 	setup_ray(data, x, y);
// 	curr_pixel[0] = send_ray(data, data->ray, data->bounce);
// 	extra_samples(data, next_ray_x, next_ray_y, curr_pixel);
// 	((unsigned int *)data->window.pxl)[x + (y * data->window.x)] =
// 			curr_pixel[0];
// }

// static int         uniformize_color(int *color, int nb)
// {
//     char        ret[4];

//     ret[0] = 0xFF;
//     ret[1] = 0;
//     ret[2] = 0;
//     ret[3] = 0;
//     for(int i = 0; i < nb; i++)
//     {
//         ret[1] = ((((char*)&(color[i]))[1] + ret[1]) / 2);
//         ret[2] = ((((char*)&(color[i]))[2] + ret[2]) / 2);
//         ret[3] = ((((char*)&(color[i]))[3] + ret[3]) / 2);
//     }
//     return (*((int *)&(*ret)));
// }

void        aa_render(t_thread *data, int *x, int *y, int *curr)
{
    unsigned int     color[5];

	*y = (*curr / data->x) + (data->pos / data->x);
	*x = *curr % data->x;
    for(int i = 0; i < data->flag.antialiasing + 1; ++i)
        color[i] = send_ray(data, setup_ray(data, *x + (((rand() % 100) - 50) / 200.0), *y + (((rand() % 100) - 50) / 200.0)), data->bounce);
    ((unsigned int *)data->pxl)[*curr] = uniformize_color(color, data->flag.antialiasing);
}