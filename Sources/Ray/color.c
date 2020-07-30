/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:17 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/30 15:11:18 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

unsigned int		set_ambiant(unsigned int base, int divide)
{
	return (0xFF000000 +
			((((unsigned char *)&base)[2] / divide) << 16) +
			((((unsigned char *)&base)[1] / divide) << 8) +
			(((unsigned char *)&base)[0] / divide));
}

unsigned int		set_color(unsigned int base, unsigned int new,
		float percent, char alpha)
{
	unsigned char	color[4];
	unsigned int	ret;

	color[0] = alpha;
	color[1] = (((base & 0xFF0000) >> 16) * (1 - percent)) +
		(((new & 0xFF0000) >> 16) * percent);
	color[2] = (((base & 0xFF00) >> 8) * (1 - percent)) +
		(((new & 0xFF00) >> 8) * percent);
	color[3] = ((base & 0xFF) * (1 - percent)) + ((new & 0xFF) * percent);
	ret = (color[0] << 24) | (color[1] << 16) | (color[2] << 8) | color[3];
	return (ret);
}

static unsigned int	find_texture_color(t_thread *data, void *obj,
		t_vec ray, int index)
{
	t_point			uv;
	unsigned int	ret;

	uv = data->txt[(int)((t_base *)obj)->effect.type](data, obj, ray, 1);
	uv.x = (int)uv.x + ((((t_base *)obj)->effect.flag & MV) ?
			((float)(data->percent / 100.0) * data->texture[index]->w) : 0);
	uv.y = (int)uv.y % data->texture[index]->h;
	uv.x = (int)uv.x % data->texture[index]->w;
	ret = ((unsigned int *)data->texture[index]->data)[(unsigned int)(uv.x +
			(uv.y * data->texture[index]->w))];
	ret = ((ret & 0xFF) << 24) +
			((ret & 0xFF00) << 8) +
			((ret & 0xFF0000) >> 8) +
			((ret & 0xFF000000) >> 24);
	return (ret);
}

static int			find_index(void *obj)
{
	if (((t_base *)obj)->effect.type == OBJ && ((t_obj *)obj)->face < 6 &&
		((t_obj *)obj)->id_texture[((t_obj *)obj)->face] != 255)
		return (((t_obj *)obj)->id_texture[((t_obj *)obj)->face]);
	return (((t_base *)obj)->effect.id_texture);
}

unsigned int		find_color(t_thread *data, void *obj, t_vec ray)
{
	Uint32	colortmp;

	if (!(((t_base *)obj)->effect.texture))
		return (((t_base *)obj)->effect.color);
	if (((t_base *)obj)->effect.id_texture < data->obj.nb_texture)
		colortmp = find_texture_color(data, obj, ray, find_index(obj));
	else
	{
		if (((t_base *)obj)->effect.id_texture == 255)
			colortmp = find_damier(data, obj, ray);
		else
			colortmp = find_perlin(data, obj, ray);
	}
	return (set_color(((t_base *)obj)->effect.color, colortmp,
		((t_base *)obj)->effect.texture / 255, ((char *)&colortmp)[0]));
}
