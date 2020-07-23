/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:37:47 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/23 11:36:20 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <thread.h>

static float		find_t(t_calc d)
{
	if (d.t0 > 0 && d.t1 > 0)
		return (d.t1 > d.t0 ? d.t0 : d.t1);
	else if (d.t0 > 0 || d.t1 > 0)
		return (d.t0 > 0 ? d.t0 : d.t1);
	return (-1);
}

static float		close_cyl(t_cylinder *c, t_vec ray)
{
	float			dot;
	t_disk			dor;

	dot = dot_product(ray.direction, c->origin.direction);
	dor.rayon = c->rayon;
	if (dot > 0)
	{
		dor.origin.origin = veccpy(c->origin.origin);
		dor.origin.direction = neg_norm(c->origin.direction);
	}
	else
	{
		dor.origin.origin = add_vec(c->origin.origin,
		mult_vec2(c->origin.direction, c->hauteur));
		dor.origin.direction = veccpy(c->origin.direction);
	}
	c->dir_close = veccpy(dor.origin.direction);
	return (disk(&dor, ray));
}

float				cylinder_2(t_cylinder **c, t_calc d, t_vec ray)
{
	float	len;
	float	cap;

	len = sqrtf(square((*c)->rayon) + square((*c)->hauteur));
	if ((*c)->hauteur != -1 && (length(sub_vec((*c)->origin.origin,
	add_vec(ray.origin,
		mult_vec2(ray.direction, d.t0)))) > len ||
		dot_product(sub_vec((*c)->origin.origin, add_vec(ray.origin,
		mult_vec2(ray.direction, d.t0))), (*c)->origin.direction) > 0))
		d.t0 = -1;
	cap = close_cyl(*c, ray);
	if (cap != -1)
	{
		if ((d.t0 != -1 && cap < d.t0) || d.t0 == -1)
		{
			(*c)->close = 1;
			(*c)->close == 1 ? d.t0 = cap : 0;
		}
	}
	return (d.t0);
}

float				cylinder(void *cylinder, t_vec ray)
{
	t_cylinder	*c;
	t_point		os;
	t_point		tmp;
	t_calc		d;

	c = (t_cylinder *)cylinder;
	c->close = 0;
	os = cross_vec(c->origin.direction, ray.direction);
	tmp = cross_vec(c->origin.direction, sub_vec(ray.origin, c->origin.origin));
	d.a = dot_product(os, os);
	d.b = dot_product(os, cross_vec(c->origin.direction,
		sub_vec(ray.origin, c->origin.origin))) * 2.0;
	d.c = dot_product(tmp, tmp) - square(c->rayon);
	d.delta = square(d.b) - (4.0 * d.a * d.c);
	if ((!d.a && d.b > 0) || d.delta < 0)
		return (-1);
	d.sqt = sqrtf(d.delta);
	d.t0 = (-d.b + sqrt(d.delta)) / (2 * d.a);
	d.t1 = (-d.b - sqrt(d.delta)) / (2 * d.a);
	d.t0 = find_t(d);
	d.t0 = cylinder_2(&c, d, ray);
	return (d.t0);
}
