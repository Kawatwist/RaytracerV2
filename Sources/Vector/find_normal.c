/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:24:32 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/19 14:21:54 by anboilea         ###   ########.fr       */
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

t_point			normal_face(Uint8 face)
{
	if (face == 0)
		return (fill_vec(0, 0, -1));
	else if (face == 1)
		return (fill_vec(0, 0, 1));
	else if (face == 2)
		return (fill_vec(0, -1, 0));
	else if (face == 3)
		return (fill_vec(0, 1, 0));
	else if (face == 4)
		return (fill_vec(-1, 0, 0));
	else if (face == 5)
		return (fill_vec(1, 0, 0));
	return (fill_vec(0, 0, 1));
}

t_point			find_normal(void *object, t_vec collide)
{
	t_point normal;

	if ((((t_base *)object)->effect.type) == SPHERE)
		normal = sub_vec(collide.origin,
			((t_base *)object)->origin.origin);
	else if ((((t_base *)object)->effect.type) == PLAN)
		normal = veccpy(((t_plan *)object)->origin.direction);
	else if ((((t_base *)object)->effect.type) == CYLINDER
		&& !((t_cylinder *)object)->close)
		normal = cylinder_normal(*((t_cylinder *)object), collide);
	else if ((((t_base *)object)->effect.type) == DISK)
		normal = veccpy(((t_plan *)object)->origin.direction);
	else if ((((t_base *)object)->effect.type) == OBJ)
		normal = normal_face(((t_obj *)object)->face);
	else if ((((t_base *)object)->effect.type) == CONE
		&& !((t_cone *)object)->close)
		normal = cone_normal(*((t_cone *)object), collide);
	else if ((((t_base *)object)->effect.type) == CYLINDER)
		normal = (veccpy(((t_cylinder *)object)->dir_close));
	else if ((((t_base *)object)->effect.type) == CONE)
		normal = (veccpy(((t_cone *)object)->dir_close));
	else
		normal = veccpy(((t_plan *)object)->origin.direction);
	return (normalize(normal));
}

t_point			find_normal_with_txt(t_thread *data, void *object, t_vec collide)
{
	t_point normal;

	normal = find_normal(object, collide);
	if (((t_base *)object)->effect.normal)
		normal = find_normal_texture(*data, object, collide, normal);
	return (normal);
}
