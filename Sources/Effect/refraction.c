/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:23:08 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/13 23:35:31 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

t_point		find_refraction(t_thread *data, void *obj, t_vec ray)
{
	float	indice;
	float	angle;
	t_point	normal;
	t_point	ret;

	normal = normalize(find_normal_with_txt(data, obj, ray));
	indice = ((t_base *)obj)->effect.id_refraction != 0 ?
		((t_base *)obj)->effect.id_refraction : 2.0;
	angle = dot_product(ray.direction, normal);
	ret = sub_vec(mult_vec2(ray.direction, indice),
		mult_vec2(normal, -angle + indice * angle));
	return (normalize(ret));
}

float		square(float f)
{
	return (f * f);
}
