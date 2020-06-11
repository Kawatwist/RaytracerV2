/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:05:46 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/11 16:00:52 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

static int		fill_effect_special(t_effect *effect, char *line)
{
	if (!ft_strncmp("\t\t\trefraction : ", line, 16))
		effect->refraction = ft_atoi(line + 16);
	else if (!ft_strncmp("\t\t\tid_refraction : ", line, 19))
		effect->id_refraction = ft_atoi(line + 19);
	else if (!ft_strncmp("\t\t\topacity : ", line, 13))
		effect->opacity = ft_atoi(line + 13);
	else if (!ft_strncmp("\t\t\treflection : ", line, 15))
		effect->reflection = ft_atoi(line + 15);
	else if (!ft_strncmp("\t\t\ttransparancy : ", line, 18))
		effect->transparancy = ft_atoi(line + 18);
	else
		return (20);
	return (0);
}

static int		fill_effect(t_effect *effect, char *line)
{
	if (!ft_strncmp("\t\t\tmv : ", line, 8))
		effect->flag += (ft_atoi(line + 8) > 0 ? MV : 0);
	else if (!ft_strncmp("\t\t\tns : ", line, 8))
		effect->flag += (ft_atoi(line + 8) > 0 ? NS : 0);
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
	else if (!fill_effect_special(effect, line))
		return (0);
	else
		return (20);
	return (0);
}

int				add_texture_face(t_data *data, char **line, int index)
{
	t_obj		*ptr;

	if (((t_base *)data->obj.item[index])->effect.type == OBJ)
	{
		ptr = ((t_obj *)data->obj.item[index]);
		if (!ft_strncmp("\t\t\tt0 :", *line, 7))
			ptr->id_texture[0] = ft_atoi(*line + 7);
		else if (!ft_strncmp("\t\t\tt1 : ", *line, 7))
			ptr->id_texture[1] = ft_atoi(*line + 7);
		else if (!ft_strncmp("\t\t\tt2 :", *line, 7))
			ptr->id_texture[2] = ft_atoi(*line + 7);
		else if (!ft_strncmp("\t\t\tt3 :", *line, 7))
			ptr->id_texture[3] = ft_atoi(*line + 7);
		else if (!ft_strncmp("\t\t\tt4 :", *line, 7))
			ptr->id_texture[4] = ft_atoi(*line + 7);
		else if (!ft_strncmp("\t\t\tt5 : ", *line, 7))
			ptr->id_texture[5] = ft_atoi(*line + 7);
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

int				add_point(t_data *data, char **line, int index)
{
	if (!ft_strncmp("\torigin :", *line, 9))
		((t_base *)data->obj.item[index])->origin.origin = get_point(*line);
	else if (!ft_strncmp("\tdirection :", *line, 12))
		((t_base *)data->obj.item[index])->origin.direction = get_point(*line);
	else if (!ft_strncmp("\tdestination :", *line, 14) &&
		((t_base *)data->obj.item[index])->effect.type)
		((t_obj *)data->obj.item[index])->destination.origin = get_point(*line);
	else if (!ft_strncmp("\tp1 :", *line, 5))
		((t_base *)data->obj.item[index])->origin.origin = get_point_y(*line);
	else if (!ft_strncmp("\tp2 : ", *line, 5))
		((t_triangle *)data->obj.item[index])->p2.origin = get_point_y(*line);
	else if (!ft_strncmp("\tp3 : ", *line, 5))
		((t_triangle *)data->obj.item[index])->p3.origin = get_point_y(*line);
	else
		return (1);
	return (0);
}

static int		other(t_data *data, char **line, int index)
{
	if (!add_point(data, line, index))
		return (0);
	else if (!ft_strncmp("\thauteur : ", *line, 11) &&
	((((t_base *)data->obj.item[index])->effect.type == CONE) ||
		(((t_base *)data->obj.item[index])->effect.type == CYLINDER)))
		((t_cone *)data->obj.item[index])->high = ft_atof(*line + 11);
	else if (!add_texture_face(data, line, index))
		return (0);
	else if (**line == (char)'#')
		return (0);
	else if (!fill_effect(&(((t_base *)data->obj.item[index])->effect),
			*line))
		return (0);
	else
		return (17);
	return (0);
}

int				fill_obj(t_data *data, char **line, int index)
{
	if (!ft_strncmp("\tcolor :", *line, 8))
		((t_base *)data->obj.item[index])->effect.color =
		((ft_atoi_base(*line + 11, 16) & 0xFFFFFF) + (255 << 24));
	else if (!ft_strncmp("\trayon : ", *line, 9) &&
	(((t_base *)data->obj.item[index])->effect.type == SPHERE ||
	((t_base *)data->obj.item[index])->effect.type == CYLINDER ||
	((t_base *)data->obj.item[index])->effect.type == DISK))
		((t_sphere *)data->obj.item[index])->rayon = ft_atof(*line + 9);
	else if (!ft_strncmp("\tsize : ", *line, 8) &&
		((t_base *)data->obj.item[index])->effect.type == OBJ)
		((t_obj *)data->obj.item[index])->size = ft_atof(*line + 8);
	else if (!ft_strncmp("\tside : ", *line, 8) &&
		((t_base *)data->obj.item[index])->effect.type == CONE)
		((t_cone *)data->obj.item[index])->side = ft_atoi(*line + 8);
	else if (!ft_strncmp("\tangle : ", *line, 9) &&
	(((t_base *)data->obj.item[index])->effect.type == CONE))
		((t_cone *)data->obj.item[index])->ang = ft_atof(*line + 9);
	else
		return (other(data, line, index));
	return (0);
}
