/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move_cam_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:10:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/23 00:45:56 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rot_cam_axe_left(t_camera *tmp)
{
	tmp->sc = add_vec(roty(sub_vec(tmp->sc, tmp->axerot), 5.0),
	tmp->axerot);
	tmp->x = roty(tmp->x, 5.0);
	tmp->y = roty(tmp->y, 5.0);
	tmp->pos.origin = add_vec(roty(sub_vec(tmp->pos.origin,
		tmp->axerot), 5.0), tmp->axerot);
	tmp->stereo->sc = add_vec(roty(sub_vec(tmp->stereo->sc,
		tmp->axerot), 5.0), tmp->axerot);
	tmp->stereo->x = roty(tmp->stereo->x, 5.0);
	tmp->stereo->y = roty(tmp->stereo->y, 5.0);
	tmp->stereo->pos.origin = add_vec(roty(sub_vec(
		tmp->stereo->pos.origin, tmp->axerot), 5.0), tmp->axerot);
}

static void	rot_cam_axe_right(t_camera *tmp)
{
	tmp->sc = add_vec(roty(sub_vec(tmp->sc, tmp->axerot),
		-5.0), tmp->axerot);
	tmp->x = roty(tmp->x, -5.0);
	tmp->y = roty(tmp->y, -5.0);
	tmp->pos.origin = add_vec(roty(sub_vec(tmp->pos.origin,
		tmp->axerot), -5.0), tmp->axerot);
	tmp->stereo->sc = add_vec(roty(sub_vec(tmp->stereo->sc,
		tmp->axerot), -5.0), tmp->axerot);
	tmp->stereo->x = roty(tmp->stereo->x, -5.0);
	tmp->stereo->y = roty(tmp->stereo->y, -5.0);
	tmp->stereo->pos.origin = add_vec(roty(sub_vec(
		tmp->stereo->pos.origin, tmp->axerot), -5.0), tmp->axerot);
}

void		rot_cam_axe(int key_code, t_camera *tmp, t_point tmp2)
{
	if (key_code == SDL_SCANCODE_UP)
	{
		tmp->sc = add_vec(rotx(sub_vec(tmp->sc, tmp2), 5.0), tmp2);
		tmp->x = rotx(tmp->x, 5.0);
		tmp->y = rotx(tmp->y, 5.0);
		tmp->stereo->sc = add_vec(rotx(sub_vec(tmp->stereo->sc,
		tmp->stereo->pos.origin), 5.0), tmp->stereo->pos.origin);
		tmp->stereo->x = rotx(tmp->stereo->x, 5.0);
		tmp->stereo->y = rotx(tmp->stereo->y, 5.0);
	}
	if (key_code == SDL_SCANCODE_DOWN)
	{
		tmp->sc = add_vec(rotx(sub_vec(tmp->sc, tmp2), -5.0), tmp2);
		tmp->x = rotx(tmp->x, -5.0);
		tmp->y = rotx(tmp->y, -5.0);
		tmp->stereo->sc = add_vec(rotx(sub_vec(tmp->stereo->sc,
		tmp->stereo->pos.origin), -5.0), tmp->stereo->pos.origin);
		tmp->stereo->x = rotx(tmp->stereo->x, -5.0);
		tmp->stereo->y = rotx(tmp->stereo->y, -5.0);
	}
	if (key_code == SDL_SCANCODE_LEFT)
		rot_cam_axe_left(tmp);
	if (key_code == SDL_SCANCODE_RIGHT)
		rot_cam_axe_right(tmp);
}
