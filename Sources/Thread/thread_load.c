/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:47:44 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/09 21:38:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		setup_perlin(t_data *data, t_thread *tmp, int x)
{
	int		i;
	int		j;

	i = -1;
	while (++i < GRADIENT)
	{
		j = -1;
		while (++j < GRADIENT)
			tmp[x].perlin[i * GRADIENT + j] = data->perlin[i * GRADIENT + j];
	}
}

static void		load_modif_other(t_data *data, t_thread *tmp, int index)
{
	ft_memcpy(&tmp[index].flag, &data->flag, sizeof(t_flag));
	setup_perlin(data, tmp, index);
}

int				load_modif(t_data *data, t_thread *tmp)
{
	static	size_t	tab[NONE] = {sizeof(t_sphere), sizeof(t_plan),
				sizeof(t_cone), sizeof(t_cylinder), sizeof(t_triangle),
				sizeof(t_disk), sizeof(t_obj)};
	int				i;

	i = -1;
	// Debug_cylinder
	// ((t_cylinder *)(data->obj.item[8]))->hauteur += 0.5;
	// ((t_cylinder *)(data->obj.item[8]))->hauteur > 10 ? ((t_cylinder *)(data->obj.item[8]))->hauteur = 1 : 0;
	//
	while (++i < 4)
	{
		ft_memcpy(&tmp[i].obj.index, &data->obj.index, 12);
		tmp[i].obj.type_index = data->obj.type_index;
		tmp[i].bounce = data->bounce;
		tmp[i].percent = data->percent;
		if (data->obj.type_index == 0)
			ft_memcpy(&tmp[i].obj.camera[data->obj.index[0]],
			&data->obj.camera[data->obj.index[0]], sizeof(t_camera));
		else if (data->obj.type_index == 1)
			ft_memcpy(tmp[i].obj.item[data->obj.index[1]],
			data->obj.item[data->obj.index[1]],
		tab[(int)((t_base*)data->obj.item[data->obj.index[1]])->effect.type]);
		else if (data->obj.type_index == 2)
			ft_memcpy(&tmp[i].obj.light[data->obj.index[2]],
			&data->obj.light[data->obj.index[2]], sizeof(t_light));
		load_modif_other(data, tmp, i);
		// Debug Cylinder
		// ((t_cylinder *)tmp[i].obj.item[8])->hauteur = ((t_cylinder *)(data->obj.item[8]))->hauteur;
		//
	}
	return (0);
}
