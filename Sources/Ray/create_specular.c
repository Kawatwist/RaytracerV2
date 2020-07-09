/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_specular.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:35:05 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/10 00:14:50 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

float			specular(t_light light,
				t_vec cam, t_vec collide)
{
	float	specular;
	t_point				l;
	t_point				v;
	t_point				r;
	static float		value = 300;

	l = sub_vec(collide.origin, light.origin);
	v = cam.direction;
	r = sub_vec(mult_vec2(collide.direction,
		dot_product(collide.direction, l) * 2), l);
	r = normalize(r);
	specular = powf(dot_product(r, v), value);
	return (specular);
}

int					create_specular(t_thread *data,
					t_ray *r, float dot, int index)
{
	int				color;

	if (dot > 0.0)
	{
		color = apply_mult(data->tmp_color, data->obj.light[index].color, dot);// calcul niveau d'ombre
		dot = specular(data->obj.light[index], data->obj.camera->pos, r->tmp);
		if (dot > 0.0)
			color = apply_mult_3(data->obj.light[index].color, color, dot);
	}
	else
		return (set_ambiant(data->ambiant, 14));
	return (color);
}
