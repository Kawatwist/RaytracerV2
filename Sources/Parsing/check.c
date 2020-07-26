/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:10:54 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/26 17:49:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	max(float a, float b)
{
	return (a < b ? b : a);
}

static float	min(float a, float b)
{
	return (a < b ? a : b);
}

static void		setup_obj(t_obj *obj)
{
	obj->low = fill_vec(min(obj->origin.origin.x, obj->destination.origin.x),
			min(obj->origin.origin.y, obj->destination.origin.y),
			min(obj->origin.origin.z, obj->destination.origin.z));
	obj->high = fill_vec(max(obj->origin.origin.x, obj->destination.origin.x),
			max(obj->origin.origin.y, obj->destination.origin.y),
			max(obj->origin.origin.z, obj->destination.origin.z));
	if (obj->size)
	{
		obj->low = sub_vec2(obj->origin.origin, obj->size / 2.0);
		obj->high = add_vec2(obj->origin.origin, obj->size / 2.0);
	}
	obj->diff = fill_vec(obj->high.x - obj->low.x, obj->high.y - obj->low.y,
		obj->high.z - obj->low.z);
}

static int		check_effect(t_data *data, t_object obj)
{
	int	index;

	index = -1;
	while (++index < obj.nb_item && obj.item[index] != NULL)
	{
		if (((t_base *)obj.item[index])->effect.type == OBJ)
			setup_obj(obj.item[index]);
		if (((t_base *)obj.item[index])->effect.id_normal > obj.nb_normal)
			return (4);
		if (((t_base *)obj.item[index])->effect.opacity)
			data->flag.diapo = 1;
	}
	index = -1;
	while (++index < obj.nb_light)
	{
		obj.light[index].distancesave = obj.light[index].distance;
		obj.light[index].intensitysave = obj.light[index].intensity;
	}
	return (0);
}

int				check_parse(t_data *data)
{
	int	val;
	int max;

	if ((val = check_effect(data, data->obj)) != 0)
		return (val);
	if ((data->input.rkey = malloc(282)) == NULL)
		return (1);
	if (data->obj.nb_texture != 0)
	{
		max = data->obj.nb_texture;
		data->obj.nb_texture = 0;
		while (data->obj.nb_texture < max && data->obj.texture[data->obj.nb_texture])
			data->obj.nb_texture += 1;
	}
	if (data->obj.nb_normal != 0)
	{
		max = data->obj.nb_normal;
		data->obj.nb_normal = 0;
		while (data->obj.nb_normal < max && data->obj.normal[data->obj.nb_normal])
			data->obj.nb_normal += 1;
	}
	return (0);
}
