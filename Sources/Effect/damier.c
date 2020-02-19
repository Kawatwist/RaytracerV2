/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 02:34:06 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/16 14:44:07 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int		damier_cylinder(t_thread *data, void *obj, t_vec ray)
{
	float	phi;
	t_point ontexture;
	t_point	u;
	t_point	v;

	u = fill_vec(((t_cylinder *)obj)->origin.direction.y,
		((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_base *)obj)->origin.direction);
	phi = atan2(sub_vec(ray.origin, ((t_base *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_base *)obj)->origin.origin).x);
	ontexture.x = 50 * (phi / (2 * M_PI));
	ontexture.y = ((float)((int)((t_base *)obj)->origin.origin.y) -
		ray.origin.y) / 10.0;
	if (((unsigned int)ontexture.x + ((unsigned int)ontexture.y)) % 2)
		return (data->ambiant);
	return (0xFF000000);
}

static int		damier_sphere(t_thread *data, void *obj, t_vec ray)
{
	t_point	ontexture;
	float	phi;
	float	theta;

	theta = acos(sub_vec(ray.origin,
		((t_sphere *)obj)->origin.origin).y / ((t_sphere *)obj)->rayon);
	phi = atan2(sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = 50 * (phi / (2 * M_PI));
	ontexture.y = 50 * ((M_PI - theta) / (M_PI));
	if (((unsigned int)ontexture.x + ((unsigned int)ontexture.y)) % 2)
		return (data->ambiant);
	return (0xFF000000);
}

static int		damier_plan(t_thread *data, void *obj, t_vec ray)
{
	t_point		u;
	t_point		v;
	t_point		uv;

	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z,
		-((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	uv.x = (unsigned int)((dot_product(ray.origin, v) - 1) * 50);
	uv.y = (unsigned int)((dot_product(ray.origin, u) - 1) * 50);
	if (((unsigned int)uv.x + ((unsigned int)uv.y)) % 2)
		return (data->ambiant);
	return (0xFF000000);
}

int				find_damier(t_thread *data, void *obj, t_vec ray)
{
	if (((t_base *)obj)->effect.type == PLAN)
		return (damier_plan(data, obj, ray));
	else if (((t_base *)obj)->effect.type == SPHERE)
		return (damier_sphere(data, obj, ray));
	return (damier_cylinder(data, obj, ray));
}
