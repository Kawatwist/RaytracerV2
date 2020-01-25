/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:20 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/25 20:42:53 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void		*check_object_light(t_thread *data, t_vec ray, float *dist)
{
	void	*close;
	int		index;
	float	value;

	*dist = -1;
	value = -1;
	close = NULL;
	index = 0;
	(void)ray;
	while (data->obj.item[index])
	{
		if (!(((t_base *)data->obj.item[index])->effect.flag & NS))
		{
			value = data->dist[(int)((t_base *)data->obj.item[index])
				->effect.type](data->obj.item[index], ray);
			if ((value > 0 && *dist == -1) || (value > 0 && value < *dist))
			{
				*dist = value;
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
	while (index < data->obj.nb_item)
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
	return (close);
}
