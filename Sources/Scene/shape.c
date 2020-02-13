/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:35:20 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/13 00:48:15 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

/*	Barycentre Triangle	*/

/*
** float		square(void *sq, t_vec ray)
** {
** 	t_triangle *t;
** 	float	f;
** 	double	v[4];
** 	double w1;
** 	double w2;
** 	t_point p;

** 	t = (t_triangle *)sq;
** 	t->origin.direction = find_normal_triangle(t);
** 	f = -dot_product(sub_vec(t->origin.origin, ray.origin), t->origin.direction) /  (-dot_product(ray.direction, t->origin.direction));
** 	p = add_vec(ray.origin, mult_vec2(ray.direction, f));
** 	v[0] = t->p3.origin.y - t->origin.origin.y;
** 	v[1] = t->p3.origin.x - t->origin.origin.x;
** 	v[2] = t->p2.origin.y - t->origin.origin.y;
** 	v[3] = p.y - t->origin.origin.y;
** 	w1 = (t->origin.origin.x * v[0] + v[3] * v[1] - p.x * v[0]) / (v[2] * v[1] - (t->p2.origin.x - t->origin.origin.x) * v[0]);
** 	w2 = (v[3]- w1 * v[2]) / v[0];
** 	if (w1 >= 0 && w2 >= 0 && w1 <= 1.0 && w2 <= 1.0)
** 		return (f);
** 	return (-1);
** }
*/

/*	Moller Version */
float		triangle(void *tri, t_vec ray)
{
	t_triangle	*t;
	t_point		tmp[5];
	double		var[4];

	t = (t_triangle *)tri;
	tmp[0] = sub_vec(t->p2.origin, t->p1.origin);
	tmp[1] = sub_vec(t->p3.origin, t->p1.origin);
	tmp[2] = cross_vec(neg_norm(ray.direction), tmp[1]);
	var[0] = dot_product(tmp[0], tmp[2]);
	if (fabs(var[0]) < 0.0001)
		return (-1);
	var[1] = 1.0 / var[0];
	tmp[3] = sub_vec(fill_vec(ray.origin.x, -ray.origin.y, ray.origin.z), t->p1.origin);
	var[2] = dot_product(tmp[3], tmp[2]) * var[1];
	if (var[2] < 0.0 || var[2] > 1.0)
		return (-1);
	tmp[4] = cross_vec(tmp[3], tmp[0]);
	var[3] = dot_product(neg_norm(ray.direction), tmp[4]) * var[1];
	if (var[3] < 0.0 || var[2] + var[3] > 1.0)
		return (-1);
	var[0] = dot_product(tmp[1], tmp[4]) * var[1];
	return (var[0] > 0.0001 ? var[0] : -1);
}

// float		triangle(void *tri, t_vec ray)
// {
// 	t_triangle *t;
// 	float	f;
// 	double	v[4];
// 	double w1;
// 	double w2;
// 	t_point p;

// 	t = (t_triangle *)tri;
// 	t->origin.direction = find_normal_triangle(t);
// 	f = -dot_product(sub_vec(t->origin.origin, ray.origin), t->origin.direction) /  (-dot_product(ray.direction, t->origin.direction));
// 	p = add_vec(ray.origin, mult_vec2(ray.direction, f));
// 	v[0] = t->p3.origin.y - t->origin.origin.y;
// 	v[1] = t->p3.origin.x - t->origin.origin.x;
// 	v[2] = t->p2.origin.y - t->origin.origin.y;
// 	v[3] = p.y - t->origin.origin.y;
// 	w1 = (t->origin.origin.x * v[0] + v[3] * v[1] - p.x * v[0]) / (v[2] * v[1] - (t->p2.origin.x - t->origin.origin.x) * v[0]);
// 	w2 = (v[3]- w1 * v[2]) / v[0];
// 	if (w1 >= 0 && w2 >= 0 && w1 + w2 < 1)
// 		return (f);
// 	return (-1);
// }

// static float		triangle_v1(void *tri, t_vec ray)
// {
// 	t_triangle	*t;
// 	t_point		pos;
// 	float		d;
// 	float		f;

// 	t = (t_triangle *)tri;
// 	t->origin.direction = find_normal_triangle(t);
// 	d = dot_product(t->origin.direction, t->origin.origin);
// 	f = -((dot_product(t->origin.direction, ray.origin) - d) /
// 		dot_product(t->origin.direction, ray.direction));
// 	pos = add_vec(ray.origin, mult_vec2(ray.direction, f));
// 	if (dot_product(t->origin.direction, cross_vec(sub_vec(t->p2.origin,
// 			t->origin.origin), sub_vec(pos, t->origin.origin))) > 0 &&
// 		dot_product(t->origin.direction, cross_vec(sub_vec(t->p3.origin,
// 			t->p2.origin), sub_vec(pos, t->p2.origin))) > 0 &&
// 		dot_product(t->origin.direction, cross_vec(sub_vec(t->origin.origin,
// 			t->p3.origin), sub_vec(pos, t->p3.origin))) > 0)
// 		return (f);
// 	return (-1);
// }


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
