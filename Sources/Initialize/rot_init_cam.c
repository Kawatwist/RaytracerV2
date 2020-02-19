/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_init_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:02:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/18 13:14:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rot_init_cam_z(t_data *data, t_point *base,
		t_point *direction, int index)
{
	float angle;

	angle = ang(acos(dot_product(fill_vec((*direction).x, (*direction).y, 0),
		fill_vec(base->x, base->y, 0))));
	(data->obj.camera[index]).sc =
		add_vec(rotz(sub_vec((data->obj.camera[index]).sc,
		(data->obj.camera[index]).pos.origin), angle),
		(data->obj.camera[index]).pos.origin);
	(data->obj.camera[index]).x =
		rotz((data->obj.camera[index]).x, angle);
	(data->obj.camera[index]).y =
		rotz((data->obj.camera[index]).y, angle);
	(*base) = normalize(veccpy(rotz((*base), angle)));
}

void	rot_init_cam_y(t_data *data, t_point *base,
		t_point *direction, int index)
{
	float	angle;

	angle = ang(acos(dot_product(fill_vec((*direction).x, 0, (*direction).z),
		fill_vec(base->x, 0, base->z))));
	(data->obj.camera[index]).sc =
		add_vec(roty(sub_vec((data->obj.camera[index]).sc,
		(data->obj.camera[index]).pos.origin), angle),
		(data->obj.camera[index]).pos.origin);
	(data->obj.camera[index]).x =
		roty((data->obj.camera[index]).x, angle);
	(data->obj.camera[index]).y =
		roty((data->obj.camera[index]).y, angle);
	(*base) = normalize(veccpy(roty((*base), angle)));
}

void	rot_init_cam_x(t_data *data, t_point *base,
		t_point *direction, int index)
{
	float	angle;

	angle = ang(acos(dot_product(fill_vec(0, (*direction).y, (*direction).z),
		fill_vec(0, base->y, base->z))));
	(data->obj.camera[index]).sc =
		add_vec(rotx(sub_vec((data->obj.camera[index]).sc,
		(data->obj.camera[index]).pos.origin), angle),
		(data->obj.camera[index]).pos.origin);
	(data->obj.camera[index]).x =
		rotx((data->obj.camera[index]).x, angle);
	(data->obj.camera[index]).y =
		rotx((data->obj.camera[index]).y, angle);
	(*base) = normalize(veccpy(rotx((*base), angle)));
}
