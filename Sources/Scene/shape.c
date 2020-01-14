/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:35:20 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/13 22:35:25 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		cone(void *coo, t_vec ray)
{
	t_calc	c;
	t_cone	*cone;
	double	k;
	t_point oc;

	cone = coo;
	k = tan(rad(cone->ang / 2.0));
	k = k * k;
	oc = sub_vec(ray.origin, cone->origin.origin);
	c.a = dot_product(ray.direction, ray.direction)
			- (1 + k) * dot_product(ray.direction, cone->origin.direction) *
			dot_product(ray.direction, cone->origin.direction);
	c.b = 2 * (dot_product(ray.direction, oc))
			- (1 + k) * dot_product(ray.direction, cone->origin.direction) *
			dot_product(oc, cone->origin.direction);
	k = dot_product(oc, oc) - (1 + k) *
			dot_product(oc, cone->origin.direction) *
			dot_product(oc, cone->origin.direction);
	c.delta = (c.b * c.b) - (4 * c.a * k);
	if (c.delta <= 0.0)
		return (-1.0);
	if ((k = (-c.b - sqrt(c.delta)) / (2.0 * c.a)) > 0)
		return (k);
	else
		return ((-c.b + sqrt(c.delta)) / (2.0 * c.a));
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
	if (!d.a && d.b)
		return (-1);
	d.delta = square(d.b) - (4.0 * d.a * d.c);
	if (d.delta < 0)
		return (-1);
	d.sqt = sqrtf(d.delta);
	if ((d.c = (((-d.b) - d.sqt) / (2.0 * d.a))) > 0)
		return (d.c);
	else
		return ((-d.b) + d.sqt / (2.0 * d.a));
	return (d.c);
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
	d.c = ((-d.b) - d.sqt) / (2.0 * d.a);
	if (d.c <= ((-d.b) + d.sqt) / (2.0 * d.a) && d.c > 0)
		return (d.c);
	else
		return (((-d.b) + d.sqt) / (2.0 * d.a));
	return (d.c);
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
