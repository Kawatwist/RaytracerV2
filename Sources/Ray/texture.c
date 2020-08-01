/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:32 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/01 21:29:58 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

t_point		texture_obj(void *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	t_point ontexture;
	t_point u;
	t_point v;

	wh = find_size(*(t_thread *)data, obj, choose);
	u = ((t_obj *)obj)->origin.direction;
	u = fill_vec(u.y, u.z, -u.x);
	v = cross_vec(u, ((t_obj *)obj)->origin.direction);
	ontexture.y = dot_product(sub_vec(((t_obj *)obj)->origin.origin,
		ray.origin), u) * (wh & 0xFFFF) +
		((wh & 0xFFFF) >> 1);
	ontexture.x = dot_product(sub_vec(((t_obj *)obj)->origin.origin,
		ray.origin), v) * (wh >> 16) + ((wh >> 16) >> 1);
	while (ontexture.x < 0 || ontexture.x >= (wh >> 16))
		ontexture.x += (ontexture.x < 0 ? (wh >> 16) - 1 : -(wh >> 16) - 1);
	while (ontexture.y < 0 || ontexture.y >= (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ?
			(wh & 0xFFFF) - 1 : -(wh & 0xFFFF) - 1);
	return (ontexture);
}

t_point		texture_plan(void *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	t_point ontexture;
	t_point u;
	t_point v;

	wh = find_size(*(t_thread *)data, obj, choose);
	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z,
		-((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	ontexture.y = (dot_product(ray.origin, u) * (wh & 0xFFFF) +
		((wh & 0xFFFF) >> 1)) * (1 / (((t_plan *)obj)->effect.height + 1));
	ontexture.x = (dot_product(ray.origin, v) * (wh >> 16) + ((wh >> 16) >> 1)) * (1 / (((t_plan *)obj)->effect.width + 1));
	while (ontexture.x < 0 || ontexture.x >= (wh >> 16))
		ontexture.x += (ontexture.x < 0 ? (wh >> 16) - 1 : -(wh >> 16) - 1);
	while (ontexture.y < 0 || ontexture.y >= (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ?
			(wh & 0xFFFF) - 1 : -(wh & 0xFFFF) - 1);
	return (ontexture);
}

t_point		texture_sphere(void *data, void *obj, t_vec ray, int choose)
{
	t_point	ontexture;
	int		wh;
	float	phi;
	float	theta;

	wh = find_size(*(t_thread *)data, obj, choose);
	theta = acos(sub_vec(ray.origin,
		((t_sphere *)obj)->origin.origin).y / ((t_sphere *)obj)->rayon);
	phi = atan2(sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = (int)(((wh & 0xFFFF) - 1) * ((M_PI - theta) / (M_PI)));
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ?
			(wh & 0xFFFF0000) >> 16 : -((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	ontexture.y = (wh & 0xFFFF) - ontexture.y;
	return (ontexture);
}

t_point		texture_cylinder(void *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	float	phi;
	t_point ontexture;
	t_point	u;
	t_point	v;

	wh = find_size(*(t_thread *)data, obj, choose);
	u = fill_vec(((t_cylinder *)obj)->origin.direction.y,
		((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_base *)obj)->origin.direction);
	phi = atan2(sub_vec(ray.origin, ((t_base *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_base *)obj)->origin.origin).x);
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = ((float)((int)ray.origin.y) - ray.origin.y) * (wh & 0xFFFF);
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ? (wh & 0xFFFF0000) >> 16 :
			-((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	return (ontexture);
}

t_point		texture_cone(void *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	t_point ontexture;
	t_point	u;
	float	phi;

	wh = find_size(*(t_thread *)data, obj, choose);
	u = fill_vec(((t_cylinder *)obj)->origin.direction.y,
		((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	phi = atan2(sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = ((float)((int)ray.origin.y) - ray.origin.y) * (wh & 0xFFFF);
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ? (wh & 0xFFFF0000) >> 16 :
			-((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	return (ontexture);
}
