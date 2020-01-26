/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cartoon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 22:49:51 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/26 21:35:53 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// float		cone(void *coo, t_vec ray)
// {
// 	t_calc	c;
// 	t_cone	*cone;
// 	t_point oc;
// 	double	k;

// 	cone = coo;
// 	oc = sub_vec(ray.origin, cone->origin.origin);
// 	k = square(tan(rad(cone->ang) / 2.0)) + 1;
// 	c.a = dot_product(ray.direction, ray.direction) -
// 		(k * dot_product(ray.direction, cone->origin.direction) *
// 		dot_product(ray.direction, cone->origin.direction));
// 	c.b = 2 * (dot_product(ray.direction, oc) -
// 		(k * dot_product(ray.direction, cone->origin.direction) *
// 		dot_product(cone->origin.direction, oc)));
// 	c.c = dot_product(oc, oc) - (k * dot_product(oc, cone->origin.direction) *
// 		dot_product(oc, cone->origin.direction));
// 	c.delta = (c.b * c.b) - (4 * c.a * c.c);
// 	c.t0 = (-c.b + sqrt(c.delta)) / (2 * c.a);
// 	c.t1 = (-c.b - sqrt(c.delta)) / (2 * c.a);
// 	if (c.t0 > 0 && c.t1 > 0)
// 		return (c.t1 > c.t0 ? c.t0 : c.t1);
// 	else if (c.t0 > 0 || c.t1 > 0)
// 		return (c.t0 > 0 ? c.t0 : c.t1);
// 	return (-1);
// }

// float		cylinder(void *cylinder, t_vec ray)//changer les nom des fonctions
// {
// 	t_cylinder	c;
// 	t_point		os;
// 	t_point		tmp;
// 	t_calc		d;

// 	c = *(t_cylinder *)cylinder;
// 	os = cross_vec(c.origin.direction, ray.direction);
// 	tmp = cross_vec(c.origin.direction, sub_vec(ray.origin, c.origin.origin));
// 	d.a = dot_product(os, os);
// 	d.b = dot_product(os, cross_vec(c.origin.direction,
// 		sub_vec(ray.origin, c.origin.origin))) * 2.0;
// 	d.c = dot_product(tmp, tmp) - square(c.rayon);
// 	d.delta = square(d.b) - (4.0 * d.a * d.c);
// 	if ((!d.a && d.b > 0) || d.delta < 0)
// 		return (-1);
// 	d.sqt = sqrtf(d.delta);
// 	d.t0 = (-d.b + sqrt(d.delta)) / (2 * d.a);
// 	d.t1 = (-d.b - sqrt(d.delta)) / (2 * d.a);
// 	if (d.t0 > 0 && d.t1 > 0)
// 		return (d.t1 > d.t0 ? d.t0 : d.t1);
// 	else if (d.t0 > 0 || d.t1 > 0)
// 		return (d.t0 > 0 ? d.t0 : d.t1);
// 	return (-1);
// }

float		sphere_depth(void *sphere, t_vec ray)
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
	if (d.delta > 0)
		return (d.t0 > d.t1 ? d.t0 - d.t1 : d.t1 - d.t0);
	return (-1);
}

// float		plane(void *plane, t_vec ray)
// {
// 	t_plan	p;
// 	float	t;
// 	float	div;

// 	p = *(t_plan *)plane;
// 	div = dot_product(ray.direction, p.origin.direction);
// 	if (div >= 0)
// 		return (-1);
// 	t = -dot_product(sub_vec(p.origin.origin, ray.origin), p.origin.direction);
// 	return (t / (-div));
// }
