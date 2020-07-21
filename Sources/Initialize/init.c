/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:11:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/21 20:35:44 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void	initialize2(t_data *data)
{
	data->txt[0] = texture_sphere;
	data->txt[1] = texture_plan;
	data->txt[2] = texture_cone;
	data->txt[3] = texture_cylinder;
	data->txt[4] = texture_plan;
	data->txt[5] = texture_plan;
	data->txt[6] = texture_obj;
	data->move[0] = move_cam;
	data->move[1] = move_obj;
	data->move[2] = move_light;
}

int			initialize(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->flag.refresh += 0b100000;
	data->flag.nb_video = 30;
	data->hud.color_obj = 1;
	data->hud.flag_hud = 0;
	data->hud.last_hud = 0;
	data->flag.typing = 0;
	data->window.x = 0;
	data->window.y = 0;
	data->dist[0] = sphere;
	data->dist[1] = plane;
	data->dist[2] = cone;
	data->dist[3] = cylinder;
	data->dist[4] = triangle;
	data->dist[5] = disk;
	data->dist[6] = obj;
	data->ambiant = 0xFF000000;
	initialize2(data);
	generate_perlin(data);

	return (0);
}
