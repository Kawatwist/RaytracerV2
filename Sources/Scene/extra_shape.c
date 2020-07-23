/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:35:46 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/23 12:07:22 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

float			triangle(void *tri, t_vec ray)
{
	t_triangle	*t;
	t_point		pos;
	float		d;
	float		f;

	t = (t_triangle *)tri;
	t->p1.direction = find_normal_triangle(t);
	d = dot_product(t->p1.direction, t->p1.origin);
	f = -((dot_product(t->p1.direction, ray.origin) - d) /
		dot_product(t->p1.direction, ray.direction));
	pos = add_vec(ray.origin, mult_vec2(ray.direction, f));
	if (dot_product(t->p1.direction, cross_vec(sub_vec(t->p2.origin,
			t->p1.origin), sub_vec(pos, t->p1.origin))) > 0 &&
		dot_product(t->p1.direction, cross_vec(sub_vec(t->p3.origin,
			t->p2.origin), sub_vec(pos, t->p2.origin))) > 0 &&
		dot_product(t->p1.direction, cross_vec(sub_vec(t->p1.origin,
			t->p3.origin), sub_vec(pos, t->p3.origin))) > 0)
		return (f);
	return (-1);
}

float			box_(t_plan p, t_vec ray, t_point diff, Uint8 side)
{
	float		t;
	t_point		dir;
	t_point		pos;
	float		div;

	dir = veccpy(p.origin.direction);
	div = dot_product(ray.direction, dir);
	if (div >= 0)
		return (-1);
	t = (-dot_product(sub_vec(p.origin.origin, ray.origin), dir) / -div);
	if (t != -1)
	{
		pos = sub_vec(add_vec(ray.origin, mult_vec2(ray.direction, t)),
			p.origin.origin);
		if (side < 2 && pos.x > 0 && pos.x < diff.x
			&& pos.y > 0 && pos.y < diff.y)
			return (t);
		else if (side < 4 && pos.x > 0 && pos.x < diff.x
			&& pos.z > 0 && pos.z < diff.z)
			return (t);
		else if (pos.y > 0 && pos.y < diff.y
			&& pos.z > 0 && pos.z < diff.z)
			return (t);
	}
	return (-1);
}

static void		obj2(Uint8 side, t_point *p, t_point *o)
{
	if (side == 1)
		p->z = o->z;
	else if (side == 3)
		p->y = o->y;
	else if (side == 5)
		p->x = o->x;
}

float			obj(void *obj, t_vec ray)
{
	float		t;
	float		save;
	t_plan		p;
	t_obj		*o;
	Uint8		side;

	o = ((t_obj *)obj);
	t = -1;
	side = -1;
	save = 99999;
	while (++side < 6)
	{
		p.origin.origin = veccpy(o->low);
		p.origin.direction = normalize(normal_face(side));
		obj2(side, &(p.origin.origin), &(o->high));
		if ((t = box_(p, ray, o->diff, side)) != -1)
		{
			save > t ? o->face = side : 0;
			save > t ? save = t : 0;
		}
	}
	if (save != 99999)
		o->origin.direction = normal_face(o->face);
	return (save == 99999 ? -1 : save);
}

float			disk(void *di, t_vec ray)
{
	t_disk		d;
	float		t;
	float		div;

	d = *(t_disk *)di;
	div = dot_product(ray.direction, d.origin.direction);
	if (div >= 0)
		return (-1);
	t = -dot_product(sub_vec(d.origin.origin, ray.origin), d.origin.direction);
	if (length(sub_vec(d.origin.origin, add_vec(ray.origin,
		mult_vec2(ray.direction, t / (-div))))) > d.rayon)
		return (-1);
	return (t / (-div));
}
