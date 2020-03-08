/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:27 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/08 01:07:16 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static t_vec		setup_refraction(t_thread data, void *obj,
		t_vec ray, float dist)
{
	t_vec tmp;

	tmp.origin = set_neworigin_op(ray, dist);
	tmp.direction = find_refraction(data, obj, ray);
	return (tmp);
}

static t_vec		setup_opacity(t_thread *data, void *obj,
		t_vec ray, float dist)
{
	t_vec tmp;

	(void)data;
	(void)obj;
	tmp.origin = set_neworigin_op(ray, dist);
	tmp.direction = veccpy(ray.direction);
	return (tmp);
}

static t_vec		setup_reflection(t_thread *data, void *obj,
		t_vec ray, float dist)
{
	t_vec tmp;

	tmp.origin = set_neworigin_neg(ray, dist);
	tmp.direction = veccpy(ray.direction);
	tmp.direction = find_reflexion(obj, tmp, *data);
	data->ray.direction = veccpy(tmp.direction);
	data->ray.origin = veccpy(tmp.origin);
	return (tmp);
}

static void			bounce_effect(t_thread *data, t_vec ray, t_ray *r)
{
	t_vec			tmp;

	if (((t_base *)r->obj)->effect.reflection)
	{
		tmp = setup_reflection(data, r->obj, ray, r->dist[0]);
		r->color[1] = send_ray(data, tmp, r->bounce);
		r->color[0] = set_color(r->color[0], r->color[1],
			((t_base *)r->obj)->effect.reflection / 255.0, -1);
	}
	if (((t_base *)r->obj)->effect.refraction)
	{
		tmp = setup_refraction(*data, r->obj, ray, r->dist[0]);
		r->color[1] = send_ray(data, tmp, r->bounce);
		r->color[0] = set_color(r->color[0], r->color[1],
			((t_base *)r->obj)->effect.refraction / 255.0, -1);
	}
	if (((t_base *)r->obj)->effect.opacity)
	{
		tmp = setup_opacity(data, r->obj, ray, r->dist[0]);
		r->color[1] = send_ray(data, tmp, r->bounce);
		r->color[0] = set_color(r->color[0], r->color[1],
			((t_base *)r->obj)->effect.opacity / 255.0, -1);
	}
}

unsigned int		send_ray(t_thread *data, t_vec ray, int bounce)
{
	int				txt;
	t_ray			r;

	if (!(r.obj = check_object(data, ray, &(r.dist[0]))) || r.dist[0] == -1)
		return (data->ambiant);
	r.tmp.origin = set_neworigin(ray, r.dist[0]);
	r.tmp.direction = veccpy(ray.direction);
	r.color[0] = find_color(data, r.obj, r.tmp);
	txt = r.color[0];
	r.tmp.origin = set_neworigin_neg(ray, r.dist[0]);
	r.tmp.direction = veccpy(ray.direction);
	r.tmp.direction = find_normal_with_txt(*data, r.obj, r.tmp);
	if (!(((t_base *)r.obj)->effect.flag & NS))
		r.color[0] = ray_to_light(data, r);
	r.bounce = bounce;
	r.bounce-- ? bounce_effect(data, ray, &r) : 0;
	if (((t_base *)r.obj)->effect.texture && ((unsigned char *)&(txt))[0] > 0
		&& ((t_base *)r.obj)->effect.transparancy)
	{
		r.tmp.origin = set_neworigin_op(ray, r.dist[0]);
		r.tmp.direction = veccpy(ray.direction);
		return (set_color(send_ray(data, r.tmp, bounce), r.color[0],
			((255 - ((unsigned char *)&(txt))[0])) / 255.0, -1));
	}
	return (r.color[0] ? r.color[0] : 0xFF000000);
}
