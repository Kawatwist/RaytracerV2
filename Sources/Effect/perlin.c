/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 23:18:51 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/22 21:53:18 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int		perlin_cylinder(t_thread *data, void *obj, t_vec ray, int type)
{
	float		phi;
	t_point		ontxt;
	t_point		u;
	t_point		v;

	u = fill_vec(((t_cylinder *)obj)->origin.direction.y,
		((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_base *)obj)->origin.direction);
	phi = atan2(sub_vec(ray.origin, ((t_base *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_base *)obj)->origin.origin).x);
	ontxt.x = (phi / (2 * M_PI)) * 10;
	ontxt.y = ((float)((int)((t_base *)obj)->origin.origin.y) -
		ray.origin.y) * 10;
	if (type == 254)
		return (perlin_color_cloud(get_perlin_cloud(data->perlin, ontxt, 4)));
	if (type == 253)
		return (perlin_color_marble(get_perlin_marble(data->perlin, ontxt)));
	return (perlin_color_wood(get_perlin_wood(data->perlin, ontxt)));
}

static int		perlin_sphere(t_thread *data, void *obj, t_vec ray, int type)
{
	t_point		ontxt;
	float		phi;
	float		theta;

	theta = acos(sub_vec(ray.origin,
		((t_sphere *)obj)->origin.origin).y / ((t_sphere *)obj)->rayon);
	phi = atan2(sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontxt.x = (phi / (2 * M_PI)) * 100;
	ontxt.y = ((M_PI - theta) / (M_PI)) * 100;
	if (type == 254)
		return (perlin_color_cloud(get_perlin_cloud(data->perlin, ontxt, 4)));
	if (type == 253)
		return (perlin_color_marble(get_perlin_marble(data->perlin, ontxt)));
	return (perlin_color_wood(get_perlin_wood(data->perlin, ontxt)));
}

static int		perlin_plan(t_thread *data, void *obj, t_vec ray, int type)
{
	t_point		u;
	t_point		v;
	t_point		uv;

	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z,
		-((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	uv.x = (dot_product(ray.origin, v));
	uv.y = (dot_product(ray.origin, u));
	if (type == 254)
		return (perlin_color_cloud(get_perlin_cloud(data->perlin, uv, 4)));
	if (type == 253)
		return (perlin_color_marble(get_perlin_marble(data->perlin, uv)));
	return (perlin_color_wood(get_perlin_wood(data->perlin, uv)));
}

int				find_perlin(t_thread *data, void *obj, t_vec ray)
{
	int id;

	id = ((t_base *)obj)->effect.id_texture;
	if (((t_base *)obj)->effect.type == PLAN)
		return (perlin_plan(data, obj, ray, id));
	else if (((t_base *)obj)->effect.type == SPHERE)
		return (perlin_sphere(data, obj, ray, id));
	return (perlin_cylinder(data, obj, ray, id));
}
