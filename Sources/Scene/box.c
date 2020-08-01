/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:47:59 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/01 16:01:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static float	box_2(t_point pos, t_point diff, float t, Uint8 side)
{
	if (side < 2)
	{
		if (pos.x > 0 && pos.x < diff.x && pos.y > 0 && pos.y < diff.y)
			return (t);
	}
	else if (side < 4)
	{
		if (pos.x > 0 && pos.x < diff.x && pos.z > 0 && pos.z < diff.z)
			return (t);
	}
	else
	{
		if (pos.y > 0 && pos.y < diff.y && pos.z > 0 && pos.z < diff.z)
			return (t);
	}
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
		return (box_2(pos, diff, t, side));
	}
	return (-1);
}
