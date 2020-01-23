/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:05 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/23 23:34:37 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int		copy_item(t_object base, t_object *dest)
{
	static	size_t	tab[4] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)};
	int		i;

	i = -1;
	while (++i < base.nb_item)
	{
		if (base.item[i] != NULL)
		{
			if ((dest->item[i] = malloc(tab[(int)((t_base *)base.item[i])->effect.type])) == NULL)
				return (1);
			ft_memcpy(dest->item[i], base.item[i], tab[(int)((t_base *)base.item[i])->effect.type]); 
		}
		else
			dest->item[i] = NULL;
	}
	return (0);
}

int		init_memory_thread(t_data *data)
{
	t_thread	*tmp;
	int			i;

	if ((data->thread = malloc(sizeof(t_thread) * 4)) == NULL)
		return (1);
	tmp = data->thread;
	ft_bzero(&(*data->thread), sizeof(t_thread) * 4);
	i = -1;
	while (++i < 4)
		if ((tmp[i].obj.item = malloc(sizeof(void *) * data->obj.nb_item)) == NULL)
			return (1);
	i = -1;
	while (++i < 4)
		if ((tmp[i].obj.light = malloc(sizeof(t_light) * data->obj.nb_light)) == NULL)
			return (1);
	i = -1;
	while (++i < 4)
		if ((tmp[i].obj.camera = malloc(sizeof(t_camera) * data->obj.nb_camera)) == NULL)
			return (1);
	i = -1;
	while (++i < 4)
		if (copy_item(data->obj, &tmp[i].obj) != 0)
			return (1);
	return (0);
}