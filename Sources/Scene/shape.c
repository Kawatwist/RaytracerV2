/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:35:20 by luwargni          #+#    #+#             */
/*   Updated: 2020/03/08 08:19:07 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

float		disk(void *di, t_vec ray)
{
	t_disk	d;
	float	t;
	float	div;

	d = *(t_disk *)di;
	div = dot_product(ray.direction, d.origin.direction);
	if (div >= 0)
		return (-1);
	t = -dot_product(sub_vec(d.origin.origin, ray.origin), d.origin.direction);
	if (length(sub_vec(d.origin.origin, add_vec(ray.origin, mult_vec2(ray.direction, t / (-div))))) > d.rayon)
		return (-1);
	return (t / (-div));
}

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

static float		find_t(t_calc d)
{
	if (d.t0 > 0 && d.t1 > 0)
		return (d.t1 > d.t0 ? d.t0 : d.t1);
	else if (d.t0 > 0 || d.t1 > 0)
		return (d.t0 > 0 ? d.t0 : d.t1);
	return (-1);
}

static float		close_cone(t_cone *c, t_vec ray, float rayon)
{
	float	dot;
	t_disk	dor;

	dot = dot_product(ray.direction, c->origin.direction);
	dor.rayon = rayon;
	if (dot > 0)
	{
		dor.origin.origin = add_vec(c->origin.origin, mult_vec2(c->origin.direction, -(c->high)));
		dor.origin.direction = neg_norm(c->origin.direction);
	}
	else if (dot < 0)
	{
		dor.origin.origin = add_vec(c->origin.origin, mult_vec2(c->origin.direction, (c->high)));
		dor.origin.direction = veccpy(c->origin.direction);
	}
	else
		return (-1);
	return (disk(&dor, ray));
}

float		cone(void *coo, t_vec ray)
{
	t_calc	c;
	t_cone	*cone;
	t_point oc;
	double	k;
	float	dot;
	float	len;
	float	rayon;

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
	c.t0 = find_t(c);
	if (c.t0 != -1 && cone->high != -1)
	{
		len = length(sub_vec(cone->origin.origin, add_vec(ray.origin, mult_vec2(ray.direction, c.t0))));
		rayon = dot_product(neg_norm(sub_vec(cone->origin.origin, add_vec(ray.origin, mult_vec2(ray.direction, c.t0)))), cone->origin.direction);
		rayon = length(sub_vec(add_vec(cone->origin.origin, mult_vec2(cone->origin.direction, rayon)), add_vec(ray.origin, mult_vec2(ray.direction, c.t0))));
	}
	dot = dot_product(sub_vec(cone->origin.origin, add_vec(ray.origin, mult_vec2(ray.direction, c.t0))), cone->origin.direction);
	if (cone->side != 0 && ((cone->side >= 1 && dot > 0) || (cone->side <= -1 && dot < 0)))
		return (-1);
	if (c.t0 != -1 && cone->high != -1 && dot_product(sub_vec(cone->origin.origin, add_vec(ray.origin, mult_vec2(ray.direction, c.t0))), cone->origin.direction) > (cone->high))
		return (close_cone(cone, ray, rayon));
	return (c.t0);
}

static float		close_cyl(t_cylinder c, t_vec ray)
{
	float	dot;
	t_disk	dor;

	dot = dot_product(ray.direction, c.origin.direction);
	dor.rayon = c.rayon;
	if (dot > 0)
	{
		dor.origin.origin = veccpy(c.origin.origin);
		dor.origin.direction = neg_norm(c.origin.direction);
	}
	else if (dot < 0)
	{
		dor.origin.origin = add_vec(c.origin.origin, mult_vec2(c.origin.direction, (c.hauteur)));
		dor.origin.direction = veccpy(c.origin.direction);
	}
	else
		return (-1);
	return (disk(&dor, ray));
}

float		cylinder(void *cylinder, t_vec ray)
{
	t_cylinder	c;
	t_point		os;
	t_point		tmp;
	t_calc		d;
	float		len;

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
	d.t0 = find_t(d);
	if (d.t0 != -1 && c.hauteur != -1)
		len = length(sub_vec(c.origin.origin, add_vec(ray.origin, mult_vec2(ray.direction, d.t0))));
	if (d.t0 != -1 && c.hauteur != -1 && (sqrtf((len * len) - (c.rayon * c.rayon)) > (c.hauteur) || dot_product(sub_vec(c.origin.origin, add_vec(ray.origin, mult_vec2(ray.direction, d.t0))), c.origin.direction) > 0))
		return (close_cyl(c, ray));
	return (d.t0);
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

/**
float		cap_cylinder(void *cyl, t_vec ray)
{
	float t;
	float a;
	t_plan bottom;
	t_plan top;

	if (((t_cylinder*)cyl)->hauteur > 0)
		return cylinder(cyl, ray);
	else
	{
		bottom.origin.origin = ((t_cylinder*)cyl)->origin.origin;
		bottom.origin.direction = ((t_cylinder*)cyl)->origin.direction;
		top.origin.origin =
		bottom.effect = ((t_cylinder*)cyl)->effect;
		t = cylinder(cyl, ray);
		a = plane(bottom,)
	}
}
**/
