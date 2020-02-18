/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:05:28 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/18 13:53:21 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int		copy_item(t_object base, t_object *dest, int nb)
{
	static	size_t	tab[5] = {sizeof(t_sphere),
								sizeof(t_plan), sizeof(t_cone),
								sizeof(t_cylinder), sizeof(t_triangle)};
	int				i;

	ft_bzero(dest->item, sizeof(void *) * (nb + 1));
	i = -1;
	while (++i < nb)
	{
		if (base.item[i] != NULL)
		{
			if ((dest->item[i] = malloc(tab[(int)((t_base *)
				base.item[i])->effect.type])) == NULL)
				return (1);
			ft_memcpy(dest->item[i], base.item[i], tab[(int)
				((t_base *)base.item[i])->effect.type]);
		}
		else
			dest->item[i] = NULL;
	}
	dest->item[i] = NULL;
	return (0);
}

static int		setup_cam_light(t_data *data, t_thread *tmp)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if ((tmp[i].obj.light = malloc(sizeof(t_light) *
			(data->obj.nb_light + 1))) == NULL)
			return (1);
		ft_memcpy((tmp[i].obj.light), (data->obj.light),
			sizeof(t_light) * data->obj.nb_light);
		tmp[i].obj.nb_light = data->obj.nb_light;
		tmp[i].obj.light[data->obj.nb_light].color = 0;
	}
	i = -1;
	while (++i < 4)
	{
		if ((tmp[i].obj.camera = malloc(sizeof(t_camera) *
			data->obj.nb_camera)) == NULL)
			return (1);
		ft_memcpy((tmp[i].obj.camera), (data->obj.camera),
			sizeof(t_camera) * data->obj.nb_camera);
		tmp[i].obj.nb_camera = data->obj.nb_camera;
	}
	return (0);
}

int			setup_obj(t_data *data, t_thread *tmp)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		ft_memcpy(&(tmp[i].obj), &(data->obj), sizeof(t_object));
		if ((tmp[i].obj.item = (void **)malloc(sizeof(void *) *
			(data->obj.nb_item + 1))) == NULL)
			return (1);
		tmp[i].obj.nb_item = data->obj.nb_item;
	}
	i = -1;
	while (++i < 4)
		if (copy_item(data->obj, &tmp[i].obj, data->obj.nb_item) != 0)
			return (1);
	if (setup_cam_light(data, tmp))
		return (1);
	return (0);
}
