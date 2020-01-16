/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:05:46 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/16 00:36:05 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		find_type(char *type)
{
	type = ft_strchr(type, ':');
	if (type != NULL)
	{
		if (*(type + 1) == 's')
			return (SPHERE);
		else if (*(type + 1) == 'p')
			return (PLAN);
		else if (*(type + 1) == 'c')
			return (*(type + 2) == 'o' ? CONE : CYLINDER);
	}
	return (NONE);
}

int		create_type(t_data *data, int index, int type)
{
	static	size_t	tab[4] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)};
	void			*item;

	if ((item = malloc(tab[(int)type])) == NULL)
		return (1);
	ft_bzero(&((t_base *)item)->effect, sizeof(t_effect));
	ft_bzero(item, sizeof(item));
	data->obj.item[index] = item;
	((t_base *)data->obj.item[index])->effect.type = type;
	return (0);
}

static t_point	add_rot(t_point mov, char *str)
{
	if (!ft_strncmp("rotatex : ", str, 10))
		mov.x = ft_atof(str + 10);
	else if (!ft_strncmp("rotatey : ", str, 10))
		mov.y = ft_atof(str + 10);
	else if (!ft_strncmp("rotatez : ", str, 10))
		mov.z = ft_atof(str + 10);
	return (mov);
}

static int		fill_effect(t_effect *effect, char *line)
{
	if (!ft_strncmp("\t\t\tmv : ", line, 8))
		effect->flag += (ft_atoi(line + 8) > 0 ? MV : 0);
	else if (!ft_strncmp("\t\t\tns : ", line, 8))
		effect->flag += (ft_atoi(line + 8) > 0 ? NS : 0);
	else if (!ft_strncmp("\t\t\trefraction : ", line, 16))
		effect->refraction = ft_atoi(line + 16);
	else if (!ft_strncmp("\t\t\topacity : ", line, 13))
		effect->opacity = ft_atoi(line + 13);
	else if (!ft_strncmp("\t\t\treflection : ", line, 15))
		effect->reflection = ft_atoi(line + 15);
	else if (!ft_strncmp("\t\t\trot :", line, 15))
		effect->movement = add_rot(effect->movement, line + 3);
	else if (!ft_strncmp("\t\t\ttexture : ", line, 13))
		effect->texture = ft_atoi(line + 13);
	else if (!ft_strncmp("\t\t\tnormal : ", line, 12))
		effect->normal = ft_atoi(line + 12);
	else if (!ft_strncmp("\t\t\tid_texture : ", line, 16))
		effect->id_texture = ft_atoi(line + 16);
	else if (!ft_strncmp("\t\t\tid_normal : ", line, 15))
		effect->id_normal = ft_atoi(line + 15);
	else if (!ft_strncmp("\t\t[effect]", line, 10))
		return (0);
	else
		return (11);
	return (0);
}

int				fill_obj(t_data *data, char **line, int index)
{
	if (!ft_strncmp("\torigin :", *line, 9))
		((t_base *)data->obj.item[index])->origin.origin = get_point(*line);
	else if (!ft_strncmp("\tdirection :", *line, 12))
		((t_base *)data->obj.item[index])->origin.direction = get_point(*line);
	else if (!ft_strncmp("\tcolor :", *line, 8))
		((t_base *)data->obj.item[index])->effect.color =
		((ft_atoi_base(*line + 11, 16) & 0xFFFFFF) + (255 << 24));
	else if (!ft_strncmp("\trayon : ", *line, 9) &&
	(((t_base *)data->obj.item[index])->effect.type == SPHERE ||
	((t_base *)data->obj.item[index])->effect.type == CYLINDER))
		((t_sphere *)data->obj.item[index])->rayon = ft_atof(*line + 9);
	else if (!ft_strncmp("\tangle : ", *line, 9) &&
	(((t_base *)data->obj.item[index])->effect.type == CONE))
		((t_cone *)data->obj.item[index])->ang = ft_atof(*line + 9);
	else if (!ft_strncmp("\t\t", *line, 2))
	{
		if (fill_effect(&(((t_base *)data->obj.item[index])->effect), *line))
			return (11);
	}
	else if (ft_strchr(*line, '#'))
		;
	else
		return (11);
	return (0);
}
