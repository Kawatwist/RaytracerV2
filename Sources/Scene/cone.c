/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:37:47 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/31 19:06:09 by lomasse          ###   ########.fr       */
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

static float		close_cone(t_cone *c, t_vec ray, float rayon)
{
	float			dot;
	t_disk			dor;

	dot = dot_product(normalize(sub_vec(ray.origin,
		c->origin.origin)), normalize(c->origin.direction));
	dor.rayon = rayon;
	if (dot >= 0)
	{
		dor.origin.origin = add_vec(c->origin.origin,
			mult_vec2(c->origin.direction, (c->high)));
		dor.origin.direction = veccpy(c->origin.direction);
	}
	else
	{
		dor.origin.origin = add_vec(c->origin.origin,
			mult_vec2(c->origin.direction, -(c->high)));
		dor.origin.direction = neg_norm(c->origin.direction);
	}
	c->dir_close = veccpy(dor.origin.direction);
	return (disk(&dor, ray));
}

static void			cone3(t_cone *cone, t_vec ray, t_calc *c)
{
	if (cone->high != -1)
	{
		c->len = cone->high / cos(rad(cone->ang / 2.0));
		c->rayon = sqrtf(square(c->len) - square(cone->high));
	}
	c->dot = dot_product(sub_vec(cone->origin.origin,
		add_vec(ray.origin, mult_vec2(ray.direction, c->t0))),
			cone->origin.direction);
}

static float		cone2(t_cone *cone, t_vec ray, t_calc c)
{
	float	cap;

	cone3(cone, ray, &c);
	if (cone->side != 0 && ((cone->side >= 1 && c.dot > 0)
		|| (cone->side <= -1 && c.dot < 0)))
		return (-1);
	cap = cone->high != -1 ? close_cone(cone, ray, c.rayon) : -1;
	if (cone->high != -1 && cap == -1 && c.t0 != -1 && (c.dot =
		dot_product(sub_vec(cone->origin.origin, add_vec(cone->origin.origin,
		mult_vec2(cone->origin.direction, c.dot < 0 ? cone->high :
		-cone->high))), sub_vec(set_neworigin(ray, c.t0),
		add_vec(cone->origin.origin, mult_vec2(cone->origin.direction,
		c.dot < 0 ? cone->high : -cone->high)))) < 0))
		return (-1);
	if (cap != -1)
	{
		(cone)->close = 1;
		c.t0 = cap;
	}
	return (c.t0);
}

float				cone(void *coo, t_vec ray)
{
	t_calc			c;
	t_cone			*cone;
	t_point			oc;
	double			k;

	cone = coo;
	cone->close = 0;
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
	return (cone2(cone, ray, c));
}
