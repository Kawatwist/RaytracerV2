/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:11:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/26 18:31:48 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

int			initialize(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->flag.refresh += 0b100000;
	data->flag.nb_video = 100;
	data->hud.color_obj = 1;
	data->hud.flag_hud = 0;
	data->hud.last_hud = 0;
	data->window.x = 0;
	data->window.y = 0;
	data->dist[0] = sphere;
	data->dist[1] = plane;
	data->dist[2] = cone;
	data->dist[3] = cylinder;
	data->dist[4] = triangle;
	data->dist[5] = disk;
	data->dist[6] = obj;
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
	data->ambiant = 0xFF000000;
	generate_perlin(data);
	return (0);
}
