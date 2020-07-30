/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move_cam_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:10:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/30 18:17:37 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void print_camera(t_camera tmp)
{
	printf("position %f %f %f ", tmp.pos.origin.x, tmp.pos.origin.y, tmp.pos.origin.z);
	printf("SC %f %f %f ", tmp.sc.x, tmp.sc.y, tmp.sc.z);
	printf("X %f %f %f ", tmp.x.x, tmp.x.y, tmp.x.z);
	printf("Y %f %f %f \n", tmp.y.x, tmp.y.y, tmp.y.z);
}

static void	rot_cam_input2(int key_code, t_camera *tmp, t_point tmp2)
{
	if (key_code == SDL_SCANCODE_UP)
	{
		print_camera(*tmp);
		tmp->sc = add_vec(cam_rotx(sub_vec(tmp->sc, tmp2), 5.0), tmp2);
		tmp->x = cam_rotx(tmp->x, 5.0);
		tmp->y = cam_rotx(tmp->y, 5.0);
	}
	if (key_code == SDL_SCANCODE_DOWN)
	{
		tmp->sc = add_vec(cam_rotx(sub_vec(tmp->sc, tmp2), -5.0), tmp2);
		tmp->x = cam_rotx(tmp->x, -5.0);
		tmp->y = cam_rotx(tmp->y, -5.0);
	}
	if (key_code == SDL_SCANCODE_LEFT)
	{
		print_camera(*tmp);
		tmp->sc = add_vec(cam_roty(sub_vec(tmp->sc, tmp2), 5.0), tmp2);
		//tmp->x = sub_vec(cam_roty(add_vec(tmp->pos.origin, tmp->x), 5.0), tmp->pos.origin);
		//tmp->y = sub_vec(cam_roty(add_vec(tmp->pos.origin, tmp->y), 5.0), tmp->pos.origin);
		tmp->x = cam_roty(tmp->x, 5.0);
		tmp->y = cam_roty(tmp->y, 5.0);
	}
	if (key_code == SDL_SCANCODE_RIGHT)
	{
		print_camera(*tmp);
		tmp->sc = add_vec(cam_roty(sub_vec(tmp->sc, tmp2), -5.0), tmp2);
		//tmp->x = sub_vec(cam_roty(add_vec(tmp->pos.origin, tmp->x), -5.0), tmp->pos.origin);
		//tmp->y = sub_vec(cam_roty(add_vec(tmp->pos.origin, tmp->y), -5.0), tmp->pos.origin);
		tmp->x = cam_roty(tmp->x, -5.0);
		tmp->y = cam_roty(tmp->y, -5.0);
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
	if (key_old(*data, SDL_SCANCODE_UP))
		rot_cam_input(data, SDL_SCANCODE_UP);
	if (key_old(*data, SDL_SCANCODE_DOWN))
		rot_cam_input(data, SDL_SCANCODE_DOWN);
	if (key_old(*data, SDL_SCANCODE_LEFT))
		rot_cam_input(data, SDL_SCANCODE_LEFT);
	if (key_old(*data, SDL_SCANCODE_RIGHT))
		rot_cam_input(data, SDL_SCANCODE_RIGHT);
}
