/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:14:42 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/27 16:49:59 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

float  trans_shadow_calc(float a, float b)
{
    return (a + b > 255 ? 255 : a + b);
}

float	trans_shadow(t_thread *data, t_vec *ray, int index, int bounce)
{
	void			*obj;
	float			dist;
	float			max_dist;
	float           transparency;
    float           new_trans;


	max_dist = length(sub_vec(data->obj.light[index].origin, ray->origin));
	obj = check_object(data, *ray, &dist, NULL);
    dist <= 0.01 ? dist = 0.1 : 0;
	if (!obj || bounce <= 0 || ((t_base *)obj)->effect.opacity == 0
	|| dist > max_dist)
		return (0.0);
	ray->origin = set_neworigin_op(*ray, dist);
    // ***
	transparency = ((t_base *)obj)->effect.opacity;
    new_trans = trans_shadow(data, ray, index, bounce - 1);
   // printf("%f\n", trans_shadow_calc(transparency, new_trans));
	return (trans_shadow_calc(transparency, new_trans));
    // ***
}

float		shadow(t_thread *data, t_ray r, int index)
{
	float			len2;
	t_vec			ray;
	float			len;
	
    (void)len2;
	ray.origin = veccpy(r.tmp.origin);
	ray.direction = normalize(sub_vec(data->obj.light[index].origin, r.tmp.origin));
	ray.origin = add_vec(ray.origin, mult_vec2(ray.direction, 0.001));
	len = length(sub_vec(r.tmp.origin, data->obj.light[index].origin));
	if ((check_object(data, ray, &len2, r.obj)) && len2 <= len)
		return (trans_shadow(data, &ray, index, data->bounce));
	//ray.origin = veccpy(data->obj.light[index].origin);
	//ray.direction = normalize(sub_vec(r.tmp.origin, data->obj.light[index].origin));
	//if ((check_object(data, ray, &len2, r.obj)) && len2 <= len)
	//	return (0);
    	//return (trans_shadow(data, &ray, index, data->bounce));
	return (255);
}