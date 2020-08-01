/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:14:42 by anboilea          #+#    #+#             */
/*   Updated: 2020/08/01 20:48:53 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

double	trans_shadow_calc(float a, float b)
{
	return (a * (b / 255));
}

double	trans_shadow(t_thread *data, t_vec *ray, int index, int bounce)
{
	void			*obj;
	float			dist;
	double			transparency;
	double			new_trans;
	float			tmp;

	obj = check_object(data, *ray, &dist, NULL);
	ray->origin = set_neworigin_op(*ray, dist);
	if (!obj || bounce <= 0)
		return (-1);
	else if (((t_base *)obj)->effect.opacity == 0)
		return (0);
	transparency = ((t_base *)obj)->effect.opacity;
	new_trans = trans_shadow(data, ray, index, bounce - 1);
	if (new_trans == -1)
		return (transparency);
	else if (new_trans == 0.0)
		return (0.0);
	tmp = trans_shadow_calc(transparency, new_trans);
	return (tmp);
}

double	shadow(t_thread *data, t_ray r, int index)
{
	float			len2;
	t_vec			ray;
	float			len;

	ray.origin = veccpy(r.tmp.origin);
	ray.direction = normalize(sub_vec(data->obj.light[index].origin,
	r.tmp.origin));
	ray.origin = add_vec(ray.origin, mult_vec2(ray.direction, 0.001));
	len = length(sub_vec(r.tmp.origin, data->obj.light[index].origin));
	if ((check_object(data, ray, &len2, r.obj)) && len2 <= len)
		return (trans_shadow(data, &ray, index, data->bounce));
	return (255.0);
}
