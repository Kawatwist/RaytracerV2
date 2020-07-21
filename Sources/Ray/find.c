/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:20 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/19 17:42:25 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void		*check_object_light(t_thread *data, t_vec ray, float *dist,
		float max_dist)
{
	void	*close;
	int		index;
	float	value;

	value = -1;
	close = NULL;
	index = 0;
	while (index < data->obj.nb_item && data->obj.item[index])
	{
		if (!(((t_base *)data->obj.item[index])->effect.flag & NS))
		{
			if (data->flag.diapo)
			{
				value = data->dist[(int)((t_base *)data->obj.item[index])
					->effect.type](data->obj.item[index], ray);
				if ((value > 0 && value < max_dist))
				{
					close = data->obj.item[index];
					value > *dist ? *dist = value : 0;
				}
			}
		}
		index += 1;
	}
	return (*dist < max_dist && *dist != -1? close : NULL);
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
	return (*dist != -1 ? close : NULL);
}
