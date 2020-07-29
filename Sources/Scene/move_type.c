/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:33:20 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/29 13:50:11 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void		move_light(t_data *data, void **light)
{
	static char ctrl = 0;

	if (key_hold(data, SDL_SCANCODE_LCTRL))
		ctrl = 1;
	input_move_light(data, light);
	input_distance_light(data, light, ctrl);
	input_color_light(data, light, ctrl);
	input_intensity_light(data, light, ctrl);
	ctrl = 0;
}

void		move_obj(t_data *data, void **obj)
{
	static char ctrl = 0;

	if (key_hold(data, SDL_SCANCODE_LCTRL))
		ctrl = 1;
	if (*obj != NULL)
		input_move_obj(data, obj);
	input_color_obj(data, obj, ctrl);
	if (key_hold(data, KEY_G) && !ctrl &&
	((*(t_base **)obj)->effect.type == SPHERE ||
	(*(t_base **)obj)->effect.type == CYLINDER))
		(*(t_sphere **)obj)->rayon < 100.0
		? (*(t_sphere **)obj)->rayon += 0.1 : 0.0;
	else if (key_hold(data, KEY_G) && ctrl)
		(*(t_sphere **)obj)->rayon > 0.1
		? (*(t_sphere **)obj)->rayon -= 0.1 : 0.0;
	input_descartes_obj(data, obj, ctrl);
	input_id(data, obj, ctrl);
	input_textures(data, obj, ctrl);
	ctrl = 0;
}

static void	refresh_cam(t_data *data, void **cam)
{
	if (key_hold(data, SDL_SCANCODE_J))
	{
		(*(t_camera **)cam)->pos.origin =
			veccpy((*(t_camera **)cam)->oldpos.origin);
		(*(t_camera **)cam)->pos.direction =
			veccpy((*(t_camera **)cam)->oldpos.direction);
		(*(t_camera **)cam)->sc = veccpy((*(t_camera **)cam)->oldsc);
		(*(t_camera **)cam)->x = veccpy((*(t_camera **)cam)->oldx);
		(*(t_camera **)cam)->y = veccpy((*(t_camera **)cam)->oldy);
		if ((*(t_camera **)cam)->mode)
		{
			(*(t_camera **)cam)->stereo->pos.origin =
				veccpy((*(t_camera **)cam)->stereo->oldpos.origin);
			(*(t_camera **)cam)->stereo->pos.direction =
				veccpy((*(t_camera **)cam)->stereo->oldpos.direction);
			(*(t_camera **)cam)->stereo->sc =
			veccpy((*(t_camera **)cam)->stereo->oldsc);
			(*(t_camera **)cam)->stereo->x =
			veccpy((*(t_camera **)cam)->stereo->oldx);
			(*(t_camera **)cam)->stereo->y =
			veccpy((*(t_camera **)cam)->stereo->oldy);
		}
	}
}

static void	move_cam2(t_data *data, void **cam, t_point *tmp)
{
	if (key_hold(data, SDL_SCANCODE_S))
	{
		(*(t_camera **)cam)->pos.origin =
		sub_vec((*(t_camera **)cam)->pos.origin, mult_vec2(*tmp, 0.5));
		(*(t_camera **)cam)->sc =
		sub_vec((*(t_camera **)cam)->sc, mult_vec2(*tmp, 0.5));
		if ((*(t_camera **)cam)->mode)
		{
			(*(t_camera **)cam)->stereo->pos.origin =
			sub_vec((*(t_camera **)cam)->stereo->pos.origin,
			mult_vec2(*tmp, 0.5));
			(*(t_camera **)cam)->stereo->sc =
			sub_vec((*(t_camera **)cam)->stereo->sc, mult_vec2(*tmp, 0.5));
		}
	}
	input_move_cam(data, *tmp, cam);
	call_rot_cam(data);
}

void		move_cam(t_data *data, void **cam)
{
	t_point tmp;

	refresh_cam(data, cam);
	tmp = veccpy(data->obj.camera[data->obj.index[0]].pos.direction);
	if (key_hold(data, SDL_SCANCODE_W))
	{
		(*(t_camera **)cam)->pos.origin =
		add_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->sc =
		add_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
		if ((*(t_camera **)cam)->mode)
		{
			(*(t_camera **)cam)->stereo->pos.origin =
			add_vec((*(t_camera **)cam)->stereo->pos.origin,
			mult_vec2(tmp, 0.5));
			(*(t_camera **)cam)->stereo->sc =
			add_vec((*(t_camera **)cam)->stereo->sc, mult_vec2(tmp, 0.5));
		}
	}
	move_cam2(data, cam, &tmp);
}
