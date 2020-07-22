/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:32:44 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 22:14:38 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			preset_cam_ext(t_data *data, int index, float coef)
{
	coef = (float)data->window.y / (float)data->window.x;
	(data->obj.camera[index]).x = fill_vec(1.0 / data->window.x, 0, 0);
	(data->obj.camera[index]).y = fill_vec(0, coef / data->window.y, 0);
	(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
	fill_vec(0, (1 - coef) / 2, 0));
}

void			initialize_cam_ext(t_data *data, int index)
{
	data->obj.camera[index].stereo->oldpos.origin =
	veccpy(data->obj.camera[index].stereo->pos.origin);
	data->obj.camera[index].stereo->oldpos.direction =
	veccpy(data->obj.camera[index].stereo->pos.direction);
	data->obj.camera[index].stereo->oldsc =
	veccpy(data->obj.camera[index].stereo->sc);
	data->obj.camera[index].stereo->oldx =
	veccpy(data->obj.camera[index].stereo->x);
	data->obj.camera[index].stereo->oldy =
	veccpy(data->obj.camera[index].stereo->y);
}
