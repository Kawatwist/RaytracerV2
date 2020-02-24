/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:24:32 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/18 15:58:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

t_point			find_normal_triangle(t_triangle *t)
{
	t_point n1;
	t_point n2;
	t_point ret;

	n1 = cross_vec(sub_vec(t->p1.origin, t->p2.origin),
		sub_vec(t->p1.origin, t->p3.origin));
	n2 = cross_vec(sub_vec(t->p3.origin, t->p1.origin),
		sub_vec(t->p3.origin, t->p2.origin));
	ret = div_vec2(add_vec(n1, n2), 2.0);
	return (normalize(ret));
}

static t_point	cylinder_normal(t_cylinder c, t_vec collide)
{
	t_point oc;
	t_point normal;
	float	high;
	t_point plane;

	oc = sub_vec(collide.origin, c.origin.origin);
	high = dot_product(oc, c.origin.direction);
	plane = mult_vec2(c.origin.direction, high);
	normal = sub_vec(collide.origin, add_vec(plane, c.origin.origin));
	return (normalize(normal));
}

static t_point	cone_normal(t_cone c, t_vec collide)
{
	float	coef;
	float	dot;
	float	high;
	t_point	ret;
	t_point	oc;

	oc = sub_vec(collide.origin, c.origin.origin);
	dot = dot_product(c.origin.direction, oc);
	coef = 1 / (tan(rad(c.ang)) / 2.0);
	high = length(mult_vec2(oc, coef));
	ret = sub_vec(oc, mult_vec2(c.origin.direction,
		(dot > 0 ? -high : high)));
	return (normalize(ret));
}

t_point			find_normal(void *object, t_vec collide)
{
	t_point normal;

	if ((((t_base *)object)->effect.type) == SPHERE)
		normal = sub_vec(collide.origin,
			((t_base *)object)->origin.origin);
	else if ((((t_base *)object)->effect.type) == PLAN)
		normal = veccpy(((t_plan *)object)->origin.direction);
	else if ((((t_base *)object)->effect.type) == CYLINDER)
		normal = cylinder_normal(*((t_cylinder *)object), collide);
	else
		normal = cone_normal(*((t_cone *)object), collide);
	return (normalize(normal));
}

t_point			find_normal_with_txt(t_thread data, void *object, t_vec collide)
{
	t_point normal;

	normal = find_normal(object, collide);
	if (((t_base *)object)->effect.normal)
		normal = find_normal_texture(data, object, collide, normal);
	return (normal);
}
