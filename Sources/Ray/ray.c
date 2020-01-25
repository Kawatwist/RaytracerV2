/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:27 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/25 21:12:14 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"
// static t_vec		setup_refraction(t_thread data, void *obj,
// 		t_vec ray, float dist)
// {
// 	t_vec tmp;

// 	tmp.origin = set_neworigin_op(ray, dist);
// 	tmp.direction = find_refraction(data, obj, ray);
// 	return (tmp);
// }

// static t_vec		setup_opacity(t_thread *data, void *obj,
// 		t_vec ray, float dist)
// {
// 	t_vec tmp;

// 	(void)data;
// 	(void)obj;
// 	tmp.origin = set_neworigin_op(ray, dist);
// 	tmp.direction = veccpy(ray.direction);
// 	return (tmp);
// }

// static t_vec		setup_reflection(t_thread *data, void *obj,
// 		t_vec ray, float dist)
// {
// 	t_vec tmp;

// 	tmp.origin = set_neworigin_neg(ray, dist);
// 	tmp.direction = veccpy(ray.direction);
// 	tmp.direction = find_reflexion(obj, tmp, *data);
// 	data->ray.direction = veccpy(tmp.direction);
// 	data->ray.origin = veccpy(tmp.origin);
// 	return (tmp);
// }

// static void			bounce_effect(t_thread *data, t_vec ray, t_ray *r)
// {
// 	t_vec			tmp;

// 	if (((t_base *)r->obj)->effect.reflection)
// 	{
// 		tmp = setup_reflection(data, r->obj, ray, r->dist[0]);
// 		r->color[1] = send_ray(data, tmp, r->bounce);
// 		r->color[0] = set_color(r->color[0], r->color[1],
// 			((t_base *)r->obj)->effect.reflection / 255.0);
// 	}
// 	if (((t_base *)r->obj)->effect.refraction)
// 	{
// 		tmp = setup_refraction(*data, r->obj, ray, r->dist[0]);
// 		r->color[1] = send_ray(data, tmp, r->bounce);
// 		r->color[0] = set_color(r->color[0], r->color[1],
// 			((t_base *)r->obj)->effect.refraction / 255.0);
// 	}
// 	if (((t_base *)r->obj)->effect.opacity)
// 	{
// 		tmp = setup_opacity(data, r->obj, ray, r->dist[0]);
// 		r->color[1] = send_ray(data, tmp, r->bounce);
// 		r->color[0] = set_color(r->color[0], r->color[1],
// 			((t_base *)r->obj)->effect.opacity / 255.0);
// 	}
// }

unsigned int		send_ray(t_thread *data, t_vec ray, int bounce)
{
	t_ray			r;

	(void)bounce;
	if (!(r.obj = check_object(data, ray, &(r.dist[0]))) || r.dist[0] == -1)
		return (0xFF000000);
	r.tmp.origin = set_neworigin(ray, r.dist[0]);
	r.tmp.direction = veccpy(ray.direction);
	r.color[0] = find_color(data, r.obj, r.tmp);
	r.tmp.origin = set_neworigin_neg(ray, r.dist[0]);
	r.tmp.direction = veccpy(ray.direction);
	r.tmp.direction = find_normal(r.obj, r.tmp);
	if (!(((t_base *)r.obj)->effect.flag & NS))
		r.color[0] = ray_to_light(data, ray, r.tmp, r.color[0]);
	// r.bounce = bounce;
	// return (r.color[0]);
	// if (r.bounce--)
	// 	bounce_effect(data, ray, &r);
	return (r.color[0] ? r.color[0] : 0xFF000000);
}
