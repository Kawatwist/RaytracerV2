/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:05:46 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/05 21:16:24 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
