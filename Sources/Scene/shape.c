/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:35:20 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/05 02:07:32 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

/*
**	Usefull ?
**
**	else if (dot_product(neg_norm(t->origin.direction),
**			cross_vec(edge0, C0)) > 0 &&
**		dot_product(neg_norm(t->origin.direction), cross_vec(edge1, C1)) > 0 &&
**		dot_product(neg_norm(t->origin.direction), cross_vec(edge2, C2)) > 0)
**		return (f);
*/

float		triangle(void *tri, t_vec ray)
{
	t_triangle	*t;
	t_point		pos;
	float		d;
	float		f;

	t = (t_triangle *)tri;
	t->origin.direction = find_normal_triangle(t);
	d = dot_product(t->origin.direction, t->origin.origin);
	f = -((dot_product(t->origin.direction, ray.origin) + d) /
		dot_product(t->origin.direction, ray.direction));
	pos = add_vec(ray.origin, mult_vec2(ray.direction, f));
	if (dot_product(t->origin.direction, cross_vec(sub_vec(t->p2.origin,
			t->origin.origin), sub_vec(pos, t->origin.origin))) > 0 &&
		dot_product(t->origin.direction, cross_vec(sub_vec(t->p3.origin,
			t->p2.origin), sub_vec(pos, t->p2.origin))) > 0 &&
		dot_product(t->origin.direction, cross_vec(sub_vec(t->origin.origin,
			t->p3.origin), sub_vec(pos, t->p3.origin))) > 0)
		return (f);
	return (-1);
}

float		cone(void *coo, t_vec ray)
{
	t_calc	c;
	t_cone	*cone;
	t_point oc;
	double	k;

	cone = coo;
	oc = sub_vec(ray.origin, cone->origin.origin);
	k = square(tan(rad(cone->ang) / 2.0)) + 1;
	c.a = dot_product(ray.direction, ray.direction) -
		(k * dot_product(ray.direction, cone->origin.direction) *
		dot_product(ray.direction, cone->origin.direction));
	c.b = 2 * (dot_product(ray.direction, oc) -
		(k * dot_product(ray.direction, cone->origin.direction) *
		dot_product(cone->origin.direction, oc)));
	c.c = dot_product(oc, oc) - (k * dot_product(oc, cone->origin.direction) *
		dot_product(oc, cone->origin.direction));
	c.delta = (c.b * c.b) - (4 * c.a * c.c);
	c.t0 = (-c.b + sqrt(c.delta)) / (2 * c.a);
	c.t1 = (-c.b - sqrt(c.delta)) / (2 * c.a);
	if (c.t0 > 0 && c.t1 > 0)
		return (c.t1 > c.t0 ? c.t0 : c.t1);
	else if (c.t0 > 0 || c.t1 > 0)
		return (c.t0 > 0 ? c.t0 : c.t1);
	return (-1);
}

float		cylinder(void *cylinder, t_vec ray)
{
	t_cylinder	c;
	t_point		os;
	t_point		tmp;
	t_calc		d;

	c = *(t_cylinder *)cylinder;
	os = cross_vec(c.origin.direction, ray.direction);
	tmp = cross_vec(c.origin.direction, sub_vec(ray.origin, c.origin.origin));
	d.a = dot_product(os, os);
	d.b = dot_product(os, cross_vec(c.origin.direction,
		sub_vec(ray.origin, c.origin.origin))) * 2.0;
	d.c = dot_product(tmp, tmp) - square(c.rayon);
	d.delta = square(d.b) - (4.0 * d.a * d.c);
	if ((!d.a && d.b > 0) || d.delta < 0)
		return (-1);
	d.sqt = sqrtf(d.delta);
	d.t0 = (-d.b + sqrt(d.delta)) / (2 * d.a);
	d.t1 = (-d.b - sqrt(d.delta)) / (2 * d.a);
	if (d.t0 > 0 && d.t1 > 0)
		return (d.t1 > d.t0 ? d.t0 : d.t1);
	else if (d.t0 > 0 || d.t1 > 0)
		return (d.t0 > 0 ? d.t0 : d.t1);
	return (-1);
}

float		sphere(void *sphere, t_vec ray)
{
	t_sphere	s;
	t_point		os;
	t_calc		d;

	s = *(t_sphere *)sphere;
	os = sub_vec(ray.origin, s.origin.origin);
	d.a = dot_product(ray.direction, ray.direction);
	d.b = dot_product(ray.direction, os) * 2.0;
	d.c = dot_product(os, os) - square(s.rayon);
	d.delta = square(d.b) - (4.0 * d.a * d.c);
	d.sqt = sqrtf(d.delta);
	d.t0 = (-d.b + sqrt(d.delta)) / (2 * d.a);
	d.t1 = (-d.b - sqrt(d.delta)) / (2 * d.a);
	if (d.t0 > 0 && d.t1 > 0)
		return (d.t1 > d.t0 ? d.t0 : d.t1);
	else if (d.t0 > 0 || d.t1 > 0)
		return (d.t0 > 0 ? d.t0 : d.t1);
	return (-1);
}

float		plane(void *plane, t_vec ray)
{
	t_plan	p;
	float	t;
	float	div;

	p = *(t_plan *)plane;
	div = dot_product(ray.direction, p.origin.direction);
	if (div >= 0)
		return (-1);
	t = -dot_product(sub_vec(p.origin.origin, ray.origin), p.origin.direction);
	return (t / (-div));
}
