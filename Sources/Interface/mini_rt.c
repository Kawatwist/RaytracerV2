/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 22:19:41 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 23:37:55 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int						mix_mini(int i, int j)
{
	unsigned char base[4];
	unsigned char light[4];
	unsigned char ret[4];

	base[0] = (i & 0xFF) >> 0;
	base[1] = (i & 0xFF00) >> 8;
	base[2] = (i & 0xFF0000) >> 16;
	base[3] = (i & 0xFF000000) >> 24;
	light[0] = (j & 0xFF) >> 0;
	light[1] = (j & 0xFF00) >> 8;
	light[2] = (j & 0xFF0000) >> 16;
	light[3] = (j & 0xFF000000) >> 24;
	ret[0] = base[0] + light[0] > 255 ? 255 : base[0] + light[0];
	ret[1] = base[1] + light[1] > 255 ? 255 : base[1] + light[1];
	ret[2] = base[2] + light[2] > 255 ? 255 : base[2] + light[2];
	ret[3] = base[3] + light[3] > 255 ? 255 : base[3] + light[3];
	i = (ret[3] << 24) + (ret[2] << 16) + (ret[1] << 8) + (ret[0] << 0);
	return (i);
}

static int				apply_mult_2(int i, float d)
{
	return (
	((int)(((int)((int)((i & 0xFF000000) >> 24) * d) << 24) & 0xFF000000) +
	(((int)(((int)((int)((i & 0xFF0000) >> 16) * d) << 16) & 0xFF0000) +
	(((int)(((int)((int)((i & 0xFF00) >> 8) * d) << 8) & 0xFF00) +
	(((int)(((int)((int)((i & 0xFF) >> 0) * d) << 0) & 0xFF)))))))));
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
		return (create_specular_mini(data, color, &r, -dot));
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
