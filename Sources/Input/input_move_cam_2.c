/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move_cam_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:10:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/29 13:49:53 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rot_cam_input2(int key_code, t_camera *tmp, t_point tmp2)
{
	if (key_code == SDL_SCANCODE_UP)
	{
		tmp->sc = add_vec(rotx(sub_vec(tmp->sc, tmp2), 5.0), tmp2);
		tmp->x = rotx(tmp->x, 5.0);
		tmp->y = rotx(tmp->y, 5.0);
	}
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
	if (data->obj.camera[data->obj.index[0]].mode == 0)
		rot_cam_input2(key_code, tmp, tmp2);
	else
		rot_cam_axe(key_code, tmp, tmp2);
}

void		call_rot_cam(t_data *data)
{
	if (key_hold(data, SDL_SCANCODE_UP))
		rot_cam_input(data, SDL_SCANCODE_UP);
	if (key_hold(data, SDL_SCANCODE_DOWN))
		rot_cam_input(data, SDL_SCANCODE_DOWN);
	if (key_hold(data, SDL_SCANCODE_LEFT))
		rot_cam_input(data, SDL_SCANCODE_LEFT);
	if (key_hold(data, SDL_SCANCODE_RIGHT))
		rot_cam_input(data, SDL_SCANCODE_RIGHT);
}
