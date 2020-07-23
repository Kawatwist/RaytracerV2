/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:10:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/23 00:41:51 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		input_move_cam2_ext(void **cam)
{
	(*(t_camera **)cam)->pos.origin =
	sub_vec((*(t_camera **)cam)->pos.origin,
	mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
	(*(t_camera **)cam)->sc =
	sub_vec((*(t_camera **)cam)->sc,
	mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
	if ((*(t_camera **)cam)->mode)
	{
		(*(t_camera **)cam)->stereo->pos.origin =
		sub_vec((*(t_camera **)cam)->stereo->pos.origin,
		mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		(*(t_camera **)cam)->stereo->sc =
		sub_vec((*(t_camera **)cam)->stereo->sc,
		mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
	}
}

void		input_move_cam2(t_data *data, void **cam)
{
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
	{
		(*(t_camera **)cam)->pos.origin =
		add_vec((*(t_camera **)cam)->pos.origin,
		mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		(*(t_camera **)cam)->sc =
		add_vec((*(t_camera **)cam)->sc,
		mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		if ((*(t_camera **)cam)->mode)
		{
			(*(t_camera **)cam)->stereo->pos.origin =
			add_vec((*(t_camera **)cam)->stereo->pos.origin,
			mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
			(*(t_camera **)cam)->stereo->sc =
			add_vec((*(t_camera **)cam)->stereo->sc,
			mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		}
	}
	if (key_old(*data, SDL_SCANCODE_SPACE))
		input_move_cam2_ext(cam);
}

void		input_move_cam_ext_1(t_data *data, t_point tmp, void **cam)
{
	tmp = roty(tmp, 90);
	(*(t_camera **)cam)->pos.origin =
	sub_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
	(*(t_camera **)cam)->sc =
	sub_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
	tmp = veccpy(data->obj.camera[data->obj.index[0]].pos.direction);
	if ((*(t_camera **)cam)->mode)
	{
		tmp = roty(tmp, 90);
		(*(t_camera **)cam)->stereo->pos.origin =
		sub_vec((*(t_camera **)cam)->stereo->pos.origin,
		mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->stereo->sc =
		sub_vec((*(t_camera **)cam)->stereo->sc,
		mult_vec2(tmp, 0.5));
		tmp = veccpy(
			data->obj.camera[data->obj.index[0]].stereo->pos.direction);
	}
}

void		input_move_cam_ext_2(t_data *data, t_point tmp, void **cam)
{
	tmp = roty(tmp, 90);
	(*(t_camera **)cam)->pos.origin =
	add_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
	(*(t_camera **)cam)->sc =
	add_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
	tmp = veccpy(data->obj.camera[data->obj.index[0]].pos.direction);
	if ((*(t_camera **)cam)->mode)
	{
		tmp = roty(tmp, 90);
		(*(t_camera **)cam)->stereo->pos.origin =
		add_vec((*(t_camera **)cam)->stereo->pos.origin,
		mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->stereo->sc =
		add_vec((*(t_camera **)cam)->stereo->sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(
			data->obj.camera[data->obj.index[0]].stereo->pos.direction);
	}
}

void		input_move_cam(t_data *data, t_point tmp, void **cam)
{
	if ((*(t_camera **)cam)->mode)
		(*(t_camera **)cam)->axerot = add_vec((*(t_camera **)cam)->pos.origin,
			div_vec2(sub_vec((*(t_camera **)cam)->stereo->pos.origin,
			(*(t_camera **)cam)->pos.origin), 2));
	if (key_old(*data, SDL_SCANCODE_D))
		input_move_cam_ext_1(data, tmp, cam);
	if (key_old(*data, SDL_SCANCODE_A))
		input_move_cam_ext_2(data, tmp, cam);
	input_move_cam2(data, cam);
}
