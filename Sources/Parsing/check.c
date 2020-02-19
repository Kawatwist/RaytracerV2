/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:10:54 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/17 20:43:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_effect(t_object obj)
{
	int	index;

	index = -1;
	while (++index < obj.nb_item && obj.item[index] != NULL)
	{
		// if (((t_base *)obj.item[index])->effect.id_texture > obj.nb_texture)
		// 	return (4);
		if (((t_base *)obj.item[index])->effect.id_normal > obj.nb_normal)
			return (4);
	}
	return (0);
}

int				check_parse(t_data *data)
{
	int	val;

	if ((val = check_effect(data->obj)) != 0)
		return (val);
	if ((data->input.rkey = malloc(282)) == NULL)
		return (1);
	return (0);
}
