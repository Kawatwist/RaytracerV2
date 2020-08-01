/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 00:42:56 by luwargni          #+#    #+#             */
/*   Updated: 2020/08/01 20:32:44 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

static float		stop_light(t_thread *data, t_light light,
		t_vec ray, float max_dist)
{
	float	intersect;
	void	*obj;
	t_vec	check;

	intersect = -1;
	check.origin = veccpy(ray.origin);
	check.direction = normalize(sub_vec(light.origin, ray.origin));
	data->obj.color_find[1] = light.color;
	data->obj.color_find[0] = light.color;
	obj = check_object_light(data, check, &intersect, max_dist);
	if (obj == NULL || intersect <= 0)
		return (-1);
	return (intersect);
}

static float		dist(float *obj)
{
	if (obj[1] > 0.0 && !(obj[1] >= obj[2]))
		obj[0] = obj[1] / obj[2];
	else
		obj[0] = 1;
	return (obj[0]);
}

static void			flag_diapo(t_thread *data, float obj[3], t_ray r, int index)
{
	t_vec			ray;
	double			transparency;
	int				fix;

	fix = 0;
	if (data->flag.shadow == 1)
	{
		transparency = shadow(data, r, index);
		if (transparency != -1)
		data->tmp_color = apply_mult(data->tmp_color,
		0xffffff, transparency / 255.0);
		fix = 1;
	}
	if (data->flag.diapo && obj[1] < obj[2] && obj[1] != -1)
	{
		ray.origin = veccpy(r.tmp.origin);
		ray.direction =
		normalize(sub_vec(data->obj.light[index].origin, r.tmp.origin));
		if (fix == 0)
		data->tmp_color = light_color(r.color[0], diapo(data, &ray, index, data->bounce));
		else
			data->tmp_color = light_color(data->tmp_color,
			light_color(r.color[0], diapo(data, &ray, index, data->bounce)));
	}
}

unsigned int		spot(t_thread *data, t_ray r, int index)
{
	float			obj[3];
	float			len;
	float			dot;
	float			dot2;

	dot = (((dot_product(normalize(sub_vec(r.tmp.origin,
		data->obj.light[index].origin)),
		normalize(neg_norm(r.tmp.direction))))));
	len = data->obj.light[index].distance - length(sub_vec(r.tmp.origin,
		data->obj.light[index].origin));
	obj[2] = length(sub_vec(data->obj.light[index].origin, r.tmp.origin));
	obj[1] = stop_light(data, data->obj.light[index], r.tmp, obj[2]);
	if (!data->flag.diapo && obj[1] < obj[2] && obj[1] != -1)
		return (0x0);
	obj[0] = (dist(obj));
	len < 0 ? len = 0 : 0;
	dot = (dot < 0 ? 0 : dot * data->obj.light[index].intensity);
	flag_diapo(data, obj, r, index);
	dot2 = dot_product(normalize(data->obj.light[index].direction),
		normalize(sub_vec(r.tmp.origin, data->obj.light[index].origin)));
	dot2 = (dot2 - data->obj.light[index].ang) *
	(1 / data->obj.light[index].ang);
	dot *= dot2;
	return (create_specular(data, &r, dot2 > 0 ? dot : 0, index));
}

unsigned int		omni(t_thread *data, t_ray r, int index)
{
	float			obj[3];
	float			len;
	float			dot;

	dot = (((dot_product(normalize(sub_vec(r.tmp.origin,
		data->obj.light[index].origin)),
		normalize(neg_norm(r.tmp.direction))))));
	len = data->obj.light[index].distance - length(sub_vec(r.tmp.origin,
		data->obj.light[index].origin));
	obj[2] = length(sub_vec(data->obj.light[index].origin, r.tmp.origin));
	obj[1] = stop_light(data, data->obj.light[index], r.tmp, obj[2]);
	if (!data->flag.diapo && obj[1] < obj[2] && obj[1] != -1)
		return (0x0);
	obj[0] = (dist(obj));
	len < 0 ? len = 0 : 0;
	dot = (dot < 0 ? 0 : dot * data->obj.light[index].intensity);
	flag_diapo(data, obj, r, index);
	return (create_specular(data, &r, dot, index));
}
