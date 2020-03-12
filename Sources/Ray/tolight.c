/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolight.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/12 11:10:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static unsigned int	add_color(unsigned int base, unsigned int new)
{
	unsigned char	color[4];

	color[3] = 0xFF;
	color[2] = (((base & 0xFF0000) >> 16)) + (((new & 0xFF0000) >> 16)) > 255
			? 255 : (((base & 0xFF0000) >> 16)) + (((new & 0xFF0000) >> 16));
	color[1] = (((base & 0xFF00) >> 8)) + (((new & 0xFF00) >> 8)) > 255 ? 255
			: (((base & 0xFF00) >> 8)) + (((new & 0xFF00) >> 8));
	color[0] = ((base & 0xFF)) + ((new & 0xFF)) > 255 ? 255 : ((base & 0xFF))
			+ ((new & 0xFF));
	return (*((int *)color));
}

int			light_color(unsigned int color, unsigned int newcolor)
{
	unsigned char	value[4];
	int				tmp;

	if ((((newcolor & 0xFF) * (color & 0xFF)) / 255) > 255)
		value[0] = 255;
	else if ((((newcolor & 0xFF) * (color & 0xFF)) / 255) < 0)
		value[0] = 0;
	else
		value[0] = ((newcolor & 0xFF) * (color & 0xFF)) / 255;
	if ((tmp = (((newcolor & 0xFF00) >> 8) *
			((color & 0xFF00) >> 8) / 255)) > 255)
		value[1] = 255;
	else
		value[1] = tmp;
	if ((tmp = (((newcolor & 0xFF0000) >> 16) *
			((color & 0xFF0000) >> 16) / 255)) > 255)
		value[2] = 255;
	else
		value[2] = tmp;
	value[3] = 255;
	return (*(int*)(value));
}

float				stop_light(t_thread *data, t_light light, t_vec ray, float max_dist)
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

	dot = -dot_product(normalize(neg_norm(data->obj.light[index].direction)), normalize(sub_vec(r.tmp.origin, data->obj.light[index].origin)));
	if (dot > data->obj.light[index].ang)
		;
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
	if (data->flag.diapo)
		return (add_color(color, light_color(r.color[0], set_color(data->obj.color_find[0],
			data->obj.color_find[0], (dot * obj[0] * len), -1))));
	return (add_color(color, light_color(r.color[0], set_color(0,
		data->obj.color_find[0], (dot * obj[0] * len), -1))));
}

unsigned int		omni(t_thread *data, t_ray r, unsigned int color, int index)
{
	float				obj[3];
	float				len;
	float				dot;

	dot = (((dot_product(normalize(sub_vec(r.tmp.origin,
		data->obj.light[index].origin)),
		normalize(neg_norm(r.tmp.direction))))));
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
	if (data->flag.diapo)
		color = add_color(color, light_color(r.color[0], set_color(data->obj.color_find[0],
			data->obj.color_find[0], (dot * obj[0] * len), -1)));
	else
		color = add_color(color, light_color(r.color[0], set_color(0,
			data->obj.color_find[0], (dot * obj[0] * len), -1)));
	r.color[0] = color;
	return (create_specular(data, color, &r, dot));
}

unsigned int		ray_to_light(t_thread *data, t_ray r)
{
	int		color;
	int		index;

	index = -1;
	color = data->ambiant;
	while (++index < data->obj.nb_light + 1)
	{
		if (data->obj.light[index].type == 1)
			color = spot(data, r, color, index);
		else
			color = omni(data, r, color, index);
	}
	return (color);
}
