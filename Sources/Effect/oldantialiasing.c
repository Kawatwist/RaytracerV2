/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldantialiasing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:17:04 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/05 01:30:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Old AntiAliasing (Need to be resetup on the new version)
**
**	static void		extra_samples(t_data *data, t_vec next_ray_x,
**						t_vec next_ray_y, unsigned int curr_pixel[16])
**	{
**		int		x;
**		int		y;
**		int 	tmp;
**		t_vec	curr_ray;
**
**		tmp = data->flag.antialiasing + 1;
**		y = -1;
**		while (y++ < data->flag.antialiasing + 1)
**		{
**			x = -1;
**			while (x++ < data->flag.antialiasing + 1)
**			{
**				curr_ray.direction = add_vec(data->ray.direction,
**					add_vec(mult_vec2(div_vec2(sub_vec(next_ray_x.direction,
**					data->ray.direction), -tmp), x),
**					mult_vec2(div_vec2(sub_vec(next_ray_y.direction,
**					data->ray.direction), -tmp), y)));
**				if (x + (y * tmp) != 0)
**					curr_pixel[x + (y * tmp)] =
**						send_ray(data, curr_ray, data->bounce);
**			}
**		}
**	uniformize_color(curr_pixel, tmp);
**	}
**
**	void	super_sample(t_data *data, int x, int y)
**	{
**		t_vec			next_ray_x;
**		t_vec			next_ray_y;
**		unsigned int 	curr_pixel[16];
**
**		setup_ray(data, x + 1, y);
**		next_ray_x = data->ray;
**		setup_ray(data, x, y + 1);
**		next_ray_y = data->ray;
**		setup_ray(data, x, y);
**		curr_pixel[0] = send_ray(data, data->ray, data->bounce);
**		extra_samples(data, next_ray_x, next_ray_y, curr_pixel);
**		((unsigned int *)data->window.pxl)[x + (y * data->window.x)] =
**				curr_pixel[0];
**	}
**
**	static int	uniformize_color(int *color, int nb)
**	{
**		char	ret[4];
**
**		ret[0] = 0xFF;
**		ret[1] = 0;
**		ret[2] = 0;
**		ret[3] = 0;
**		for(int i = 0; i < nb; i++)
**		{
**			ret[1] = ((((char*)&(color[i]))[1] + ret[1]) / 2);
**			ret[2] = ((((char*)&(color[i]))[2] + ret[2]) / 2);
**			ret[3] = ((((char*)&(color[i]))[3] + ret[3]) / 2);
**		}
**		return (*((int *)&(*ret)));
**	}
*/
