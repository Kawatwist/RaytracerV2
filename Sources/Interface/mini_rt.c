/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 22:19:41 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/08 23:40:06 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float			specular(t_light light,
				t_vec cam, t_vec collide)
{
	float				specular;
	t_point				l;
	t_point				v;
	t_point				r;

	l = sub_vec(collide.origin, light.origin);
	v = cam.direction;
	r = sub_vec(mult_vec2(collide.direction,
		dot_product(collide.direction, l) * 2), l);
	r = normalize(r);
	specular = powf(dot_product(r, v), 13);
	return (specular);
}

static int				create_specular(t_data *data, int color,
				t_ray *r, float dot)
{
	color = apply_mult(color,
		data->screen.preview.light.color, dot);
	dot = specular(data->screen.preview.light,
		data->screen.preview.cam, r->tmp);
	color = data->screen.preview.sphere.effect.color;
	if (dot > 0.0)
		color = apply_mult_3(data->screen.preview.light.color,
			color, dot);
	return (color);
}

static int				find_color(t_data *data, t_vec ray, t_ray r, float dist)
{
	int					color;
	float				dot;
	t_point				new_point;
	t_point				l2n;

	new_point = set_neworigin(ray, dist);
	l2n = normalize(sub_vec(new_point, data->screen.preview.light.origin));
	r.tmp.origin = veccpy(new_point);
	new_point = normalize(sub_vec(new_point,
		data->screen.preview.sphere.origin.origin));
	r.tmp.direction = veccpy(new_point);
	dot = dot_product(l2n, new_point);
	if (dot < 0)
	{
		color = data->screen.preview.sphere.effect.color;
		return (create_specular(data, color, &r, -dot));
	}
	else
		return (apply_mult_2(data->screen.preview.sphere.effect.color,
			1 - dot));
}

static t_vec			set_ray(void)
{
	t_vec		ray;

	ray.origin = fill_vec(0, 0, 0);
	ray.origin.y = -(300 / 2.0);
	ray.direction = fill_vec(0, 0, 1);
	return (ray);
}

void					mini_rt(t_data *data)
{
	t_vec				ray;
	t_ray				r;
	float				dist;

	ray = set_ray();
	ft_bzero(&r, sizeof(r));
	while (ray.origin.y < (300 / 2.0))
	{
		ray.origin.x = -(300 / 2.0);
		while (ray.origin.x < 300 / 2.0)
		{
			if ((dist = sphere(&data->screen.preview.sphere, ray)) != -1)
				((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) +
					((150 + (int)ray.origin.y) * 300)] =
					find_color(data, ray, r, dist);
			else
				((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) +
					((150 + (int)ray.origin.y) * 300)] = 0x22222222;
			ray.origin.x += 1.0;
		}
		ray.origin.y += 1.0;
	}
}
