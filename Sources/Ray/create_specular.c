/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_specular.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:35:05 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/01 23:26:49 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"


int				mix(int i, int j)
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

int				apply_mult_3(int i, int j, float d)
{
	int fix;

	fix =
	((int)(((int)((int)((i & 0xFF000000) >> 24) * d) << 24) & 0xFF000000) +
		(((int)(((int)((int)((i & 0xFF0000) >> 16) * d) << 16) & 0xFF0000) +
		(((int)(((int)((int)((i & 0xFF00) >> 8) * d) << 8) & 0xFF00) +
		(((int)(((int)((int)((i & 0xFF) >> 0) * d) << 0) & 0xFF))))))));
	fix = mix(j, fix);
	return (fix);
}


int				apply_mult_2(int i, float d)
{
	return (
	((int)(((int)((int)((i & 0xFF000000) >> 24) * d) << 24) & 0xFF000000) +
	(((int)(((int)((int)((i & 0xFF0000) >> 16) * d) << 16) & 0xFF0000) +
	(((int)(((int)((int)((i & 0xFF00) >> 8) * d) << 8) & 0xFF00) +
	(((int)(((int)((int)((i & 0xFF) >> 0) * d) << 0) & 0xFF)))))))));
}

int				apply_mult(int i, int j, float d)
{
	unsigned char base[4];
	unsigned char light[4];
	unsigned char ret[4];

(void)d;
	base[0] = (i & 0xFF) >> 0;
	base[1] = (i & 0xFF00) >> 8;
	base[2] = (i & 0xFF0000) >> 16;
	base[3] = (i & 0xFF000000) >> 24;
	light[0] = (j & 0xFF) >> 0;
	light[1] = (j & 0xFF00) >> 8;
	light[2] = (j & 0xFF0000) >> 16;
	light[3] = (j & 0xFF000000) >> 24;
	ret[0] = sqrtf(base[0] * light[0]);
	ret[1] = sqrtf(base[1] * light[1]);
	ret[2] = sqrtf(base[2] * light[2]);
	ret[3] = sqrtf(base[3] * light[3]);
	i = (ret[3] << 24) + (ret[2] << 16) + (ret[1] << 8) + (ret[0] << 0);
	i = apply_mult_2(i, d);
	return (i);
}


// static int	set_specular(t_thread *data, int color, unsigned int specobj, float dot)
// {
// 	color = (((int)(((data->obj.light[0].color & 0xFF000000) >> 24) * dot) << 24) +
// 			((int)(((data->obj.light[0].color & 0xFF0000) >> 16) * dot) << 16) +
// 			((int)(((data->obj.light[0].color & 0xFF00) >> 8) * dot) << 8) +
// 			((int)(((data->obj.light[0].color & 0xFF) >> 0) * dot) << 0) +
// 			((int)(((specobj & 0xFF000000) >> 24) * (1.0 - dot)) << 24) +
// 			((int)(((specobj & 0xFF0000) >> 16) * (1.0 - dot)) << 16) +
// 			((int)(((specobj & 0xFF00) >> 8) * (1.0 - dot)) << 8) +
// 			((int)(((specobj & 0xFF) >> 0) * (1.0 - dot)) << 0));
// 	return (color);
// }


float			specular(t_light light,
				t_vec cam, t_vec collide)
{
	float	specular;
	t_point				l;
	t_point				v;
	t_point				r;
	static float		value = 700;

	l = sub_vec(collide.origin, light.origin);
	v = cam.direction;
	r = sub_vec(mult_vec2(collide.direction,
		dot_product(collide.direction, l) * 2), l);
	r = normalize(r);
	specular = powf(dot_product(r, v), value);
	return (specular);
}

int			create_specular(t_thread *data, int color, t_ray *r, float dot, int index)
{
	if (dot > 0.0)
	{
		color = apply_mult(((t_base *)r->obj)->effect.color, data->obj.light[index].color, dot);
		dot = specular(data->obj.light[index], data->obj.camera->pos, r->tmp);
		if (dot > 0.0)
			color = apply_mult_3(data->obj.light[index].color, color, dot);
	}
	else
		return (data->ambiant);
	return (color);
}

