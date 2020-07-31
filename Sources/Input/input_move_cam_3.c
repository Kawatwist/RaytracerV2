/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move_cam_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:10:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/31 14:08:55 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rot_cam_axe_right(t_camera *tmp)
{
	tmp->sc = add_vec(cam_rot(sub_vec(tmp->sc, tmp->axerot), 5.0, tmp->y),
	tmp->axerot);
	tmp->x = cam_rot(tmp->x, 5.0, tmp->y);
	tmp->y = cam_rot(tmp->y, 5.0, tmp->y);
	tmp->pos.origin = add_vec(cam_rot(sub_vec(tmp->pos.origin,
		tmp->axerot), 5.0, tmp->y), tmp->axerot);
	tmp->stereo->sc = add_vec(cam_rot(sub_vec(tmp->stereo->sc,
		tmp->axerot), 5.0, tmp->y), tmp->axerot);
	tmp->stereo->x = cam_rot(tmp->stereo->x, 5.0, tmp->y);
	tmp->stereo->y = cam_rot(tmp->stereo->y, 5.0, tmp->y);
	tmp->stereo->pos.origin = add_vec(cam_rot(sub_vec(
		tmp->stereo->pos.origin, tmp->axerot), 5.0, tmp->y), tmp->axerot);
}

static void	rot_cam_axe_left(t_camera *tmp)
{
	tmp->sc = add_vec(cam_rot(sub_vec(tmp->sc, tmp->axerot),
		-5.0, tmp->y), tmp->axerot);
	tmp->x = cam_rot(tmp->x, -5.0, tmp->y);
	tmp->y = cam_rot(tmp->y, -5.0, tmp->y);
	tmp->pos.origin = add_vec(cam_rot(sub_vec(tmp->pos.origin,
		tmp->axerot), -5.0, tmp->y), tmp->axerot);
	tmp->stereo->sc = add_vec(cam_rot(sub_vec(tmp->stereo->sc,
		tmp->axerot), -5.0, tmp->y), tmp->axerot);
	tmp->stereo->x = cam_rot(tmp->stereo->x, -5.0, tmp->y);
	tmp->stereo->y = cam_rot(tmp->stereo->y, -5.0, tmp->y);
	tmp->stereo->pos.origin = add_vec(cam_rot(sub_vec(
		tmp->stereo->pos.origin, tmp->axerot), -5.0, tmp->y), tmp->axerot);
}

void		rot_cam_axe(int key_code, t_camera *tmp, t_point tmp2)
{
	if (key_code == SDL_SCANCODE_UP)
	{
		tmp->sc = add_vec(cam_rot(sub_vec(tmp->sc, tmp2), 5.0, tmp->x), tmp2);
		tmp->x = cam_rot(tmp->x, 5.0, tmp->x);
		tmp->y = cam_rot(tmp->y, 5.0, tmp->x);
		tmp->stereo->sc = add_vec(cam_rot(sub_vec(tmp->stereo->sc,
		tmp->stereo->pos.origin), 5.0, tmp->x), tmp->stereo->pos.origin);
		tmp->stereo->x = cam_rot(tmp->stereo->x, 5.0, tmp->x);
		tmp->stereo->y = cam_rot(tmp->stereo->y, 5.0, tmp->x);
	}
	if (key_code == SDL_SCANCODE_DOWN)
	{
		tmp->sc = add_vec(cam_rot(sub_vec(tmp->sc, tmp2), -5.0, tmp->x), tmp2);
		tmp->x = cam_rot(tmp->x, -5.0, tmp->x);
		tmp->y = cam_rot(tmp->y, -5.0, tmp->x);
		tmp->stereo->sc = add_vec(cam_rot(sub_vec(tmp->stereo->sc,
		tmp->stereo->pos.origin), -5.0, tmp->x), tmp->stereo->pos.origin);
		tmp->stereo->x = cam_rot(tmp->stereo->x, -5.0, tmp->x);
		tmp->stereo->y = cam_rot(tmp->stereo->y, -5.0, tmp->x);
	}
	if (key_code == SDL_SCANCODE_LEFT)
		rot_cam_axe_left(tmp);
	if (key_code == SDL_SCANCODE_RIGHT)
		rot_cam_axe_right(tmp);
}
