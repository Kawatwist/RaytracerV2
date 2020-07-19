/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 00:42:56 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/19 17:54:30 by lomasse          ###   ########.fr       */
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

unsigned int		spot(t_thread *data, t_ray r, unsigned int color, int index)
{
	float	obj[3];
	float	len;
	float	dot;

	dot = -dot_product(normalize(neg_norm(data->obj.light[index].direction)),
		normalize(sub_vec(r.tmp.origin, data->obj.light[index].origin)));
	if (dot < data->obj.light[index].ang)
		return (data->ambiant);
	len = data->obj.light[index].distance - length(sub_vec(r.tmp.origin,
		data->obj.light[index].origin));
	obj[2] = length(sub_vec(data->obj.light[index].origin, r.tmp.origin));
	obj[1] = stop_light(data, data->obj.light[index], r.tmp, obj[2]);
	obj[0] = (dist(obj));
	len > 1 ? len = 1 : 0;
	len < 0 ? len = 0 : 0;
	dot > 1 ? dot = 1 : 0;
	dot < 0 ? dot = 0 : 0;
	dot *= data->obj.light[index].intensity;
	color = add_color(color, light_color(r.color[0], set_color(0,
			data->obj.color_find[0], (dot * obj[0] * len), -1)));
	return (create_specular(data, &r, dot, index));
}


unsigned int		omni(t_thread *data, t_ray r, unsigned int color, int index)
{
	float				obj[3];
	float				len;
	float				dot;
	t_vec				ray;

	(void)color;
	dot = (((dot_product(normalize(sub_vec(r.tmp.origin,
		data->obj.light[index].origin)),
		normalize(neg_norm(r.tmp.direction))))));
	len = data->obj.light[index].distance - length(sub_vec(r.tmp.origin,
		data->obj.light[index].origin));
	obj[2] = length(sub_vec(data->obj.light[index].origin, r.tmp.origin));
	obj[1] = stop_light(data, data->obj.light[index], r.tmp, obj[2]);
	if (!data->flag.diapo && obj[1] < obj[2] && obj[1] != -1)
		return(0x0);
	obj[0] = (dist(obj));
	len < 0 ? len = 0 : 0;
	dot = (dot < 0 ? 0 : dot * data->obj.light[index].intensity);
	r.color[0] = add_color(color, light_color(r.color[0], set_color(0,
		data->obj.color_find[0], (dot * obj[0] * len), -1)));
	if (data->flag.diapo && obj[1] < obj[2] && obj[1] != -1)
	{
		ray.origin = veccpy(r.tmp.origin);
		ray.direction = normalize(sub_vec(data->obj.light[index].origin, r.tmp.origin));
		data->tmp_color = (light_color(r.color[0], diapo(data, &ray, index, data->bounce)));
	}
	return (create_specular(data, &r, dot, index));
}
