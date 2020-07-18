/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolight.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/18 15:04:46 by lomasse          ###   ########.fr       */
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
