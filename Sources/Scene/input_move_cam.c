/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:10:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/18 13:15:08 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rot_cam_input2(int key_code, t_camera *tmp, t_point tmp2)
{
	if (key_code == SDL_SCANCODE_DOWN)
	{
		tmp->sc = add_vec(rotx(sub_vec(tmp->sc, tmp2), -5.0), tmp2);
		tmp->x = rotx(tmp->x, -5.0);
		tmp->y = rotx(tmp->y, -5.0);
	}
	if (key_code == SDL_SCANCODE_LEFT)
	{
		tmp->sc = add_vec(roty(sub_vec(tmp->sc, tmp2), 5.0), tmp2);
		tmp->x = roty(tmp->x, 5.0);
		tmp->y = roty(tmp->y, 5.0);
	}
	if (key_code == SDL_SCANCODE_RIGHT)
	{
		tmp->sc = add_vec(roty(sub_vec(tmp->sc, tmp2), -5.0), tmp2);
		tmp->x = roty(tmp->x, -5.0);
		tmp->y = roty(tmp->y, -5.0);
	}
}

static void	rot_cam_input(t_data *data, int key_code)
{
	t_camera	*tmp;
	t_point		tmp2;

	tmp = &(data->obj.camera[data->obj.index[0]]);
	tmp2 = tmp->pos.origin;
	if (key_code == SDL_SCANCODE_UP)
	{
		tmp->sc = add_vec(rotx(sub_vec(tmp->sc, tmp2), 5.0), tmp2);
		tmp->x = rotx(tmp->x, 5.0);
		tmp->y = rotx(tmp->y, 5.0);
	}
	rot_cam_input2(key_code, tmp, tmp2);
}

void		call_rot_cam(t_data *data)
{
	if (key_old(*data, SDL_SCANCODE_UP))
		rot_cam_input(data, SDL_SCANCODE_UP);
	if (key_old(*data, SDL_SCANCODE_DOWN))
		rot_cam_input(data, SDL_SCANCODE_DOWN);
	if (key_old(*data, SDL_SCANCODE_LEFT))
		rot_cam_input(data, SDL_SCANCODE_LEFT);
	if (key_old(*data, SDL_SCANCODE_RIGHT))
		rot_cam_input(data, SDL_SCANCODE_RIGHT);
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
	}
	if (key_old(*data, SDL_SCANCODE_SPACE))
	{
		(*(t_camera **)cam)->pos.origin =
		sub_vec((*(t_camera **)cam)->pos.origin,
		mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		(*(t_camera **)cam)->sc =
		sub_vec((*(t_camera **)cam)->sc,
		mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
	}
}

void		input_move_cam(t_data *data, t_point tmp, void **cam)
{
	if (key_old(*data, SDL_SCANCODE_D))
	{
		tmp = roty(tmp, 90);
		(*(t_camera **)cam)->pos.origin =
		sub_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->sc =
		sub_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(data->obj.camera[data->obj.index[0]].pos.direction);
	}
	if (key_old(*data, SDL_SCANCODE_A))
	{
		tmp = roty(tmp, 90);
		(*(t_camera **)cam)->pos.origin =
		add_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->sc =
		add_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(data->obj.camera[data->obj.index[0]].pos.direction);
	}
	input_move_cam2(data, cam);
}
