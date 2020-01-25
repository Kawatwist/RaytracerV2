/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:47:44 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/25 21:13:21 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

int     load_modif(t_data *data, t_thread *tmp)
{
	static	size_t	tab[4] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)};
    int     i;

    i = -1;
    while (++i < 4)
    {
        if (data->obj.type_index == 0)
            ft_memcpy(&tmp[i].obj.camera[data->obj.index[0]], &data->obj.camera[data->obj.index[0]], sizeof(t_camera));
        else if (data->obj.type_index == 1)
            ft_memcpy(&tmp[i].obj.item[data->obj.index[1]], &data->obj.item[data->obj.index[1]], tab[(int)((t_base*)data->obj.item[data->obj.index[1]])->effect.type]);
        else if (data->obj.type_index == 2)
            ft_memcpy(&tmp[i].obj.light[data->obj.index[2]], &data->obj.light[data->obj.index[2]], sizeof(t_light));
        ft_memcpy(&tmp[i].flag, &data->flag, sizeof(t_flag));
    }
    return (0);
}