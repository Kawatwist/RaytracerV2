/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:33:09 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/12 03:13:49 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				find_type(char *type)
{
	type = ft_strchr(type, ':');
	if (type != NULL)
	{
		if (*(type + 1) == 's')
			return (SPHERE);
		else if (*(type + 1) == 'p')
			return (PLAN);
		else if (*(type + 1) == 't')
			return (TRIANGLE);
		else if (*(type + 1) == 'd')
			return (DISK);
		else if (*(type + 1) == 'o')
			return (OBJ);
		else if (*(type + 1) == 'c')
			return (*(type + 2) == 'o' ? CONE : CYLINDER);
	}
	return (NONE);
}

int				create_type(t_data *data, int index, int type)
{
	static	size_t	tab[NONE] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)
			, sizeof(t_triangle), sizeof(t_disk), sizeof(t_obj)};
	void			*item;

	if ((item = malloc(tab[(int)type])) == NULL)
		return (1);
	ft_bzero(&((t_base *)item)->effect, sizeof(t_effect));
	ft_bzero(item, sizeof(item));
	data->obj.item[index] = item;
	((t_base *)data->obj.item[index])->effect.type = type;
	if (type == OBJ)
		for (int i = 0; i < 6; i++)
			((t_obj *)data->obj.item[index])->id_texture[i] = 255;
	return (0);
}
