/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:23:08 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/24 20:32:50 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

t_point		find_refraction(t_thread data, void *obj, t_vec ray)
{
	float	indice;
	float	angle;
	t_point	normal;
	t_point	ret;

	normal = normalize(find_normal_with_txt(data, obj, ray));
	indice = 2;
	angle = dot_product(ray.direction, normal);
	ret.x = ray.direction.x * indice - normal.x * (-angle + indice * angle);
	ret.y = ray.direction.y * indice - normal.y * (-angle + indice * angle);
	ret.z = ray.direction.z * indice - normal.z * (-angle + indice * angle);
	return (normalize(ret));
}

float		square(float f)
{
	return (f * f);
}
