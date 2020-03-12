/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:20 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/12 17:29:26 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void		set_color_light(t_thread *data, t_vec ray, int index, float dist)
{
	// t_vec	tmp;

	(void)dist;
	// tmp.origin = veccpy(ray.origin);
	// tmp.direction = add_vec(ray.origin, mult_vec2(ray.direction, dist));
	if (index == 0)
		data->obj.color_find[0] = light_color(data->obj.color_find[1],
			set_color(0, find_color(data, ((t_base *)data->obj.item[index]),
			ray), ((t_base *)data->obj.item[index])->effect.opacity / 255.0, -1));
	else
		data->obj.color_find[0] = light_color(data->obj.color_find[0],
			set_color(0, find_color(data, ((t_base *)data->obj.item[index]),
			ray), ((t_base *)data->obj.item[index])->effect.opacity / 255.0, -1));
}

void		*check_object_light(t_thread *data, t_vec ray, float *dist, float max_dist)
{
	void	*close;
	int		index;
	int		index2;
	float	value;

	*dist = -1;
	value = -1;
	close = NULL;
	index = 0;
	index2 = 0;

(void)max_dist;
	(void)ray;
	while (data->obj.item[index])
	{
		if (!(((t_base *)data->obj.item[index])->effect.flag & NS))
		{
			value = data->dist[(int)((t_base *)data->obj.item[index])
				->effect.type](data->obj.item[index], ray);
			if ((value > 0 && value < max_dist))
			{
				if (*dist == -1 || value < *dist)
					*dist = value;
				if (data->flag.diapo && data->obj.color_find[0])
				{
					set_color_light(data, ray, index2, value);
					index2++;
				}
				close = data->obj.item[index];
			}
		}
		index++;
	}
	return (close);
}

void		*check_object(t_thread *data, t_vec ray, float *dist)
{
	void	*close;
	int		index;
	float	value;

	*dist = -1;
	value = -1;
	close = NULL;
	index = 0;
	while (index < data->obj.nb_item && ((t_base *)data->obj.item[index]))
	{
		value = data->dist[(int)((t_base *)data->obj.item[index])
			->effect.type](data->obj.item[index], ray);
		if ((value > 0 && *dist == -1) || (value > 0 && value < *dist))
		{
			*dist = value;
			close = data->obj.item[index];
		}
		index++;
	}
	//if (close != NULL && data->flag.filter == 3 &&
	//	((t_base *)close)->effect.type == SPHERE)
	//	if (sphere_depth(close, ray) < 1)
	//		return (NULL);
	return (*dist < 4000 ? close : NULL);
}
