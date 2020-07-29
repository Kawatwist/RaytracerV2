/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:14:42 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/29 16:02:56 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

float  trans_shadow_calc(float a, float b)
{
	if (b - a >= -255.0)
    	return (-255.0);
	return (b - a);

}

float	trans_shadow(t_thread *data, t_vec *ray, int index, int bounce)
{
	void			*obj;
	float			dist;
	float           transparency;
    float           new_trans;

	obj = check_object(data, *ray, &dist, NULL);
	if (!obj)
		return (255); 
	 if (bounce <= 0 || ((t_base *)obj)->effect.opacity == 0)
	 		return (0);
	ray->origin = set_neworigin_op(*ray, dist);
	transparency = ((t_base *)obj)->effect.opacity;
    new_trans = trans_shadow(data, ray, index, bounce - 1);
	return (trans_shadow_calc(transparency, new_trans));
 
}

float		shadow(t_thread *data, t_ray r, int index, int boo)
{
	float			len2;
	t_vec			ray;
	float			len;
	float			tmp = 0.0;
	float			tmp2 = 0.0;
	
    (void)len2;
	ray.origin = veccpy(r.tmp.origin);
	ray.direction = normalize(sub_vec(data->obj.light[index].origin, r.tmp.origin));
	ray.origin = add_vec(ray.origin, mult_vec2(ray.direction, 0.001));
	len = length(sub_vec(r.tmp.origin, data->obj.light[index].origin));

(void)boo;
(void)tmp;
(void)tmp2;
	
	if ((check_object(data, ray, &len2, r.obj)) && len2 <= len)
	{
		tmp = (trans_shadow(data, &ray, index, data->bounce));
		return (tmp);
	}
	
	//**********Calcul Inside ou object a une seule face ********************
	/*
	ray.origin = veccpy(data->obj.light[index].origin);
	ray.direction = normalize(sub_vec(r.tmp.origin, data->obj.light[index].origin));
	if ((check_object(data, ray, &len2, r.obj)) && len2 <= len)
    {
		tmp2 = (trans_shadow(data, &ray, index, data->bounce));
		//printf("%f\n", tmp2);
		return (tmp2);
	}
	/*
	
	return (255);
}