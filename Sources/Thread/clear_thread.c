/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 23:31:39 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/06 04:14:28 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		clear_texture(t_thread *data, t_tga **tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_texture - 1 && (tofree[i])->data)
	{
		ft_memdel((void **)&(tofree[i])->data);
		ft_memdel((void **)&tofree[i]);
	}
	if (tofree != NULL)
		ft_memdel((void **)&(tofree));
}

static void		clear_normal(t_thread *data, t_tga **tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_normal - 1 && (tofree[i])->data)
	{
		ft_memdel((void **)&(tofree[i])->data);
		ft_memdel((void **)&tofree[i]);
	}
	if (tofree != NULL)
		ft_memdel((void **)&(tofree));
}

static void		clear_obj_item(t_object tofree, int nb_item)
{
	int		i;

	i = -1;
	while (i++ < nb_item - 1 && (tofree).item)
		tofree.item[i] != NULL ? ft_memdel((void **)&tofree.item[i]) : 0;
	if (tofree.item != NULL)
		ft_memdel((void **)&tofree.item);
}

int				clear_thread(t_thread *data)
{
	int	i;

	i = -1;
	while (++i < 4 && &(data[i]) != NULL)
	{
		clear_obj_item(data[i].obj, data[i].obj.nb_item);
		clear_texture(data, data[i].texture);
		clear_normal(data, data[i].normal);
		ft_memdel((void **)&(data[i].obj.camera));
		ft_memdel((void **)&(data[i].obj.light));
	}
	return (0);
}
