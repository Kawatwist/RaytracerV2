/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:32:44 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/26 13:44:26 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		setup_stereo(t_data *data, t_camera *cam)
{
	cam->stereo->x = veccpy(cam->x);
	cam->stereo->y = veccpy(cam->y);
	cam->stereo->sc = sub_vec(cam->sc, mult_vec2(cam->x, data->window.x / 4.0));
	cam->stereo->pos.origin =
	sub_vec(cam->pos.origin, mult_vec2(cam->x, data->window.x / 4.0));
	cam->stereo->pos.direction = veccpy(cam->pos.direction);
	cam->axerot = sub_vec(cam->pos.origin,
	mult_vec2(cam->x, data->window.x / 8.0));
}

static int		preset_cam(t_data *data, int index)
{
	float	coef;

	coef = 0.0;
	(data->obj.camera[index]).sc =
		add_vec((data->obj.camera[index]).pos.origin,
			fill_vec(-0.5, -0.5, 0.5));
	if (data->window.x >= data->window.y)
	{
		coef = (float)data->window.x / (float)data->window.y;
		(data->obj.camera[index]).x = fill_vec(coef / data->window.x, 0, 0);
		(data->obj.camera[index]).y = fill_vec(0, 1.0 / data->window.y, 0);
		(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
			fill_vec((1 - coef) / 2.0, 0, 0));
	}
	else
		preset_cam_ext(data, index, coef);
	if (data->obj.camera[index].mode != 0)
	{
		if (!(data->obj.camera[index].stereo = malloc(sizeof(t_camera))))
			return (1);
		setup_stereo(data, &data->obj.camera[index]);
	}
	return (0);
}

static void		apply_rot(t_data *data, t_point base,
	t_point direction, int index)
{
	if (!data->obj.camera[index].mode)
	{
		if (direction.y != base.y && direction.z != base.z)
			rot_init_cam_x(data, &base, &direction, index);
		if (direction.x != base.x && direction.z != base.z)
			rot_init_cam_y(data, &base, &direction, index);
		if (direction.x != base.x && direction.y != base.y)
			rot_init_cam_z(data, &base, &direction, index);
	}
}

int				initialize_cam(t_data *data)
{
	int			index;
	t_point		direction;
	t_point		base;

	index = 0;
	while (index < data->obj.nb_camera)
	{
		direction = normalize((data->obj.camera[index]).pos.direction);
		base = fill_vec(0, 0, 1);
		if (preset_cam(data, index))
			return (1);
		if (!data->obj.camera[index].mode)
			apply_rot(data, base, direction, index);
		data->obj.camera[index].oldpos.origin =
			veccpy(data->obj.camera[index].pos.origin);
		data->obj.camera[index].oldpos.direction =
			veccpy(data->obj.camera[index].pos.direction);
		data->obj.camera[index].oldsc = veccpy(data->obj.camera[index].sc);
		data->obj.camera[index].oldx = veccpy(data->obj.camera[index].x);
		data->obj.camera[index].oldy = veccpy(data->obj.camera[index].y);
		if (data->obj.camera[index].mode)
			initialize_cam_ext(data, index);
		index++;
	}
	return (0);
}
