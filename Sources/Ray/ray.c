/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:27 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/30 18:06:28 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static float		ext_bounce_effect_send_ray(t_ray *r, int boo)
{
	if (boo == 1)
		return (r->use_alpha ? ((r->alpha / 255.0 +
	((t_base *)r->obj)->effect.opacity / 255.0)) :
	((t_base *)r->obj)->effect.opacity / 255.0);
	else
	{
		r->use_alpha = 1;
		r->alpha = ((r->color[0] & 0xFF000000) >> 24);
	}
	return (0);
}

static void			bounce_effect(t_thread *data, t_vec ray, t_ray *r)
{
	t_vec			tmp;
	float			val;

	if (((t_base *)r->obj)->effect.reflection)
	{
		tmp = setup_reflection(data, ray, r->dist[0]);
		r->color[1] = send_ray(data, tmp, r->bounce, r->obj);
		r->color[0] = set_color(r->color[0], r->color[1],
			((t_base *)r->obj)->effect.reflection / 255.0, -1);
	}
	if (((t_base *)r->obj)->effect.refraction)
	{
		tmp = setup_refraction(data, r->obj, ray, r->dist[0]);
		r->color[1] = send_ray(data, tmp, r->bounce + 1, r->obj);
		r->color[0] = set_color(r->color[0], r->color[1],
			((t_base *)r->obj)->effect.refraction / 255.0, -1);
	}
	if (((t_base *)r->obj)->effect.opacity || r->use_alpha)
	{
		tmp = setup_opacity(data, r->obj, ray, r->dist[0]);
		r->color[1] = send_ray(data, tmp, r->bounce + 1, NULL);
		val = ext_bounce_effect_send_ray(r, 1);
		val > 1 ? val = 1 : 0;
		r->color[0] = set_color(r->color[0], r->color[1], val, -1);
	}
}

static unsigned int	send_ray_txt(t_ray *r, t_thread *data, t_vec *ray,
	int *bounce)
{
	r->tmp.origin = set_neworigin_op(*ray, r->dist[0]);
	r->tmp.direction = veccpy(ray->direction);
	return (set_color(send_ray(data, r->tmp, *bounce, NULL), r->color[0],
		((255 - ((unsigned char *)&(data->tmp_color))[0])) / 255.0, -1));
}

static unsigned int	send_ray2(t_thread *data, t_vec ray,
					int bounce, t_ray r)
{
	if (((t_base *)r.obj)->effect.texture &&
		((unsigned char *)&(data->tmp_color))[0] > 0
		&& ((t_base *)r.obj)->effect.transparancy)
		send_ray_txt(&r, data, &ray, &bounce);
	if (data->flag.normal && r.bounce <= 0)
		return ((int)((r.tmp.direction.x + 1) * (255 / 2.0)) +
		((int)((r.tmp.direction.y + 1) * (255 / 2.0)) << 8) +
		((int)((r.tmp.direction.z + 1) * (255 / 2.0)) << 16));
		return (r.color[0]);
}

unsigned int		send_ray(t_thread *data, t_vec ray,
					int bounce, void *ignore)
{
	t_ray			r;

	r.use_alpha = 0;
	if (!(r.obj = check_object(data, ray, &(r.dist[0]), ignore))
		|| r.dist[0] == -1)
		return (data->ambiant);
	r.tmp.origin = set_neworigin(ray, r.dist[0]);
	if (((data->dist_ray = length(sub_vec(r.tmp.origin, ray.origin))) >
		data->max_dist) && data->max_dist)
		return (data->ambiant);
	r.tmp.direction = veccpy(ray.direction);
	r.color[0] = find_color(data, r.obj, r.tmp);
	if (((t_base *)r.obj)->effect.texture &&
		((r.color[0] & 0xFF000000) >> 24) && data->flag.alpha)
		ext_bounce_effect_send_ray(&r, 2);
	data->tmp_color = r.color[0];
	r.tmp.origin = set_neworigin_neg(ray, r.dist[0]);
	r.tmp.direction = veccpy(ray.direction);
	r.tmp.direction = find_normal_with_txt(data, r.obj, r.tmp);
	if (!(((t_base *)r.obj)->effect.flag & NS))
		r.color[0] = ray_to_light(data, r);
	r.bounce = bounce;
	r.bounce-- ? bounce_effect(data, ray, &r) : 0;
	return (send_ray2(data, ray, bounce, r));
}
