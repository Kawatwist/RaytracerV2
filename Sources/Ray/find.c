/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:20 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/11 17:26:45 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void		set_color_light(t_thread *data, t_vec ray, int index, float dist)
{
	(void)dist;
	if (index == 0)
		data->obj.color_find[0] = light_color(data->obj.color_find[1],
			set_color(0, find_color(data, ((t_base *)data->obj.item[index]),
			ray), ((t_base *)data->obj.item[index])->effect.opacity / 255.0,
			-1));
	else
		data->obj.color_find[0] = light_color(data->obj.color_find[0],
			set_color(0, find_color(data, ((t_base *)data->obj.item[index]),
			ray), ((t_base *)data->obj.item[index])->effect.opacity / 255.0,
			-1));
}

void		*check_object_light(t_thread *data, t_vec ray, float *dist,
		float max_dist)
{
	void	*close;
	int		index[2];
	float	value;

	value = -1;
	close = NULL;
	*((void **)index) = NULL;
	while (data->obj.item[index[0]])
	{
		if (!(((t_base *)data->obj.item[index[0]])->effect.flag & NS))
		{
			value = data->dist[(int)((t_base *)data->obj.item[index[0]])
				->effect.type](data->obj.item[index[0]], ray);
			if ((value > 0 && value < max_dist))
			{
				*dist == -1 || value < *dist ? *dist = value : 0;
				data->flag.diapo && data->obj.color_find[0] ?
				set_color_light(data, ray, index[1], value) : 0;
				data->flag.diapo && data->obj.color_find[0] ? index[1] += 1 : 0;
				close = data->obj.item[index[0]];
			}
		}
		index[0] += 1;
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
	return (*dist < 4000 ? close : NULL);
}
