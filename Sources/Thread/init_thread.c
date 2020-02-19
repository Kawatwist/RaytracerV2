/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:05 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/18 13:52:54 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"


static void		setup_function(t_thread *tmp)
{
	(*tmp).dist[0] = sphere;
	(*tmp).dist[1] = plane;
	(*tmp).dist[2] = cone;
	(*tmp).dist[3] = cylinder;
	(*tmp).dist[4] = triangle;
	(*tmp).txt[0] = texture_sphere;
	(*tmp).txt[1] = texture_plan;
	(*tmp).txt[2] = texture_cone;
	(*tmp).txt[3] = texture_cylinder;
	(*tmp).txt[4] = texture_plan;
	(*tmp).move[0] = move_cam;
	(*tmp).move[1] = move_obj;
	(*tmp).move[2] = move_light;
}

static int		setup_struct(t_data *data, t_thread *tmp)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		tmp[i].x = data->window.x;
		tmp[i].y = data->window.y;
		tmp[i].pxl = NULL;
		ft_memcpy(&tmp[i].flag, &data->flag, sizeof(t_flag));
		tmp[i].ray.origin = fill_vec(0, 0, 0);
		tmp[i].ray.direction = fill_vec(0, 0, 1);
		if (setup_txt_and_normal(data, &(tmp[i])))
			return (1);
		setup_function(&(tmp[i]));
		tmp[i].percent = data->percent;
		tmp[i].bounce = data->bounce;
		tmp[i].ambiant = data->ambiant;
		tmp[i].pos = i * ((data->window.y * data->window.x) >> 2);
	}
	return (0);
}

int		init_thread_memory(t_data *data)
{
	if ((data->thread = malloc(sizeof(t_thread) * 4)) == NULL)
		return (1);
	ft_bzero(&(*data->thread), sizeof(t_thread) * 4);
	if (setup_struct(data, data->thread))
		return (1);
	if (setup_obj(data, data->thread))
		return (1);
	return (0);
}
