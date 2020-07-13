/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolight.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/13 18:10:12 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

unsigned int		add_color(unsigned int base, unsigned int new)
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

int					light_color(unsigned int color, unsigned int newcolor)
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
/*
float				stop_light(t_thread *data, t_light light,
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
*/
/*
static float		dist(float *obj)
{
	if (obj[1] > 0.0 && !(obj[1] >= obj[2]))
		obj[0] = obj[1] / obj[2];
	else
		obj[0] = 1;
	return (obj[0]);
}
*/
unsigned int		ray_to_light(t_thread *data, t_ray r)
{
	int		color;
	int		index;

	index = -1;
	color = data->ambiant;
	while (++index < data->obj.nb_light + 1)
	{
		if (data->obj.light[index].type == 1)
			color = add_color(spot(data, r, data->tmp_color, index), color);/* Addition light ? */
		else
			color = add_color(omni(data, r, data->tmp_color, index), color);
	}
	return (color);
}
