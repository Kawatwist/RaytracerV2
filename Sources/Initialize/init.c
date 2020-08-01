/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:11:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/01 20:35:45 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void	initialize_scene_data(t_data *data)
{
	data->generate = 0;
	data->percent = 0;
	data->max_dist = 4000;
	data->window.x = 1000;
	data->window.y = 1000;
	data->obj.nb_camera = 1;
	data->obj.nb_light = 1;
	data->obj.nb_item = 1;
}

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
	data->screen.preview.select_section = 1;
	data->hud.flag_hud = 0;
	data->hud.last_hud = 0;
	data->flag.adv = 1;
	data->flag.typing = 0;
	data->flag.shadow = 0;
	data->flag.ambiant = 1;
	data->dist[0] = sphere;
	data->dist[1] = plane;
	data->dist[2] = cone;
	data->dist[3] = cylinder;
	data->dist[4] = triangle;
	data->dist[5] = disk;
	data->dist[6] = obj;
	data->ambiant = 0xFF000000;
	initialize2(data);
	initialize_scene_data(data);
	generate_perlin(data);
	if (init_case(data, 0))
		return (1);
	return (0);
}
