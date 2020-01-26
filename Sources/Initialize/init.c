/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:11:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/24 20:21:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

int		initialize(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->flag.refresh += 0b100000;
	data->window.x = 0;
	data->window.y = 0;
	data->dist[0] = sphere;
	data->dist[1] = plane;
	data->dist[2] = cone;
	data->dist[3] = cylinder;
	data->txt[0] = texture_sphere;
	data->txt[1] = texture_plan;
	data->txt[2] = texture_cone;
	data->txt[3] = texture_cylinder;
	data->move[0] = move_cam;
	data->move[1] = move_obj;
	data->move[2] = move_light;
	return (0);
}
