/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:46:46 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/04 21:53:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Id_rotation currently not Used
**
**	if (key_check(*data, SDL_SCANCODE_KP_6) && !ctrl)
**		(*(t_base **)obj)->effect.id_rotation += 1;
**	else if (key_check(*data, SDL_SCANCODE_KP_6) && ctrl)
**		(*(t_base **)obj)->effect.id_rotation -= 1;
*/

void	input_id(t_data *data, void **obj, char ctrl)
{
	if (key_check(*data, SDL_SCANCODE_KP_4) && !ctrl &&
	(*(t_base **)obj)->effect.id_texture < data->obj.nb_texture - 1)
		(*(t_base **)obj)->effect.id_texture += 1;
	else if (key_check(*data, SDL_SCANCODE_KP_4) && ctrl &&
	(*(t_base **)obj)->effect.id_texture > 0)
		(*(t_base **)obj)->effect.id_texture -= 1;
	if (key_check(*data, SDL_SCANCODE_KP_5) && !ctrl &&
	(*(t_base **)obj)->effect.id_normal < data->obj.nb_normal - 1)
		(*(t_base **)obj)->effect.id_normal += 1;
	else if (key_check(*data, SDL_SCANCODE_KP_5) && ctrl &&
	(*(t_base **)obj)->effect.id_normal > 0)
		(*(t_base **)obj)->effect.id_normal -= 1;
}

void	input_descartes_obj(t_data *data, void **obj, char ctrl)
{
	t_effect	*tmp;

	tmp = &(*(t_base **)obj)->effect;
	if (key_old(*data, SDL_SCANCODE_KP_1) && !ctrl && tmp->reflection < 255)
		tmp->reflection += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_1) && ctrl && tmp->reflection > 0)
		tmp->reflection -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_2) && !ctrl && tmp->refraction < 255)
		tmp->refraction += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_2) && ctrl && tmp->refraction > 0)
		tmp->refraction -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_3) && !ctrl && tmp->opacity < 255)
		tmp->opacity += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_3) && ctrl && tmp->opacity > 0)
		tmp->opacity -= 1;
}

void	input_color_obj(t_data *data, void **obj, char ctrl)
{
	if (key_old(*data, SDL_SCANCODE_KP_7) && !ctrl &&
	((*(t_base **)obj)->effect.color & 0xFF0000) >> 16 < 255)
		((char *)&((*(t_base **)obj)->effect.color))[2] += 1;
	if (key_old(*data, SDL_SCANCODE_KP_7) && ctrl &&
	((*(t_base **)obj)->effect.color & 0xFF0000) >> 16 > 0)
		((char *)&((*(t_base **)obj)->effect.color))[2] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_8) && !ctrl &&
	((*(t_base **)obj)->effect.color & 0xFF00) >> 8 < 255)
		((char *)&((*(t_base **)obj)->effect.color))[1] += 1;
	if (key_old(*data, SDL_SCANCODE_KP_8) && ctrl &&
	((*(t_base **)obj)->effect.color & 0xFF00) >> 8 > 0)
		((char *)&((*(t_base **)obj)->effect.color))[1] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_9) && !ctrl &&
	((*(t_base **)obj)->effect.color & 0xFF) < 255)
		((char *)&((*(t_base **)obj)->effect.color))[0] += 1;
	if (key_old(*data, SDL_SCANCODE_KP_9) && ctrl &&
	((*(t_base **)obj)->effect.color & 0xFF) > 0)
		((char *)&((*(t_base **)obj)->effect.color))[0] -= 1;
}

static void change_point(float *p1, float *p2, float *p3, float value)
{
	*p1 += value;
	*p2 += value;
	*p3 += value;
}

static void	mv_triangle(t_data *data, t_triangle **obj)
{
	if (key_old(*data, SDL_SCANCODE_SPACE))
		change_point(&(*obj)->origin.origin.y, &(*obj)->p2.origin.y, &(*obj)->p3.origin.y , -0.1);
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
		change_point(&(*obj)->origin.origin.y, &(*obj)->p2.origin.y, &(*obj)->p3.origin.y , 0.1);
	if (key_old(*data, SDL_SCANCODE_A))
		change_point(&(*obj)->origin.origin.x, &(*obj)->p2.origin.x, &(*obj)->p3.origin.x , -0.1);
	if (key_old(*data, SDL_SCANCODE_D))
		change_point(&(*obj)->origin.origin.x, &(*obj)->p2.origin.x, &(*obj)->p3.origin.x , 0.1);
	if (key_old(*data, SDL_SCANCODE_W))
		change_point(&(*obj)->origin.origin.z, &(*obj)->p2.origin.z, &(*obj)->p3.origin.z , -0.1);
	if (key_old(*data, SDL_SCANCODE_S))
		change_point(&(*obj)->origin.origin.z, &(*obj)->p2.origin.z, &(*obj)->p3.origin.z , 0.1);
}

void	input_move_obj(t_data *data, void **obj)
{
	if ((*(t_base **)obj)->effect.type == TRIANGLE)
		mv_triangle(data, (t_triangle **)obj);
	else
	{
		if (key_old(*data, SDL_SCANCODE_SPACE))
			(*(t_base **)obj)->origin.origin.y -= 0.1;
		if (key_old(*data, SDL_SCANCODE_LSHIFT))
			(*(t_base **)obj)->origin.origin.y += 0.1;
		if (key_old(*data, SDL_SCANCODE_A))
			(*(t_base **)obj)->origin.origin.x -= 0.1;
		if (key_old(*data, SDL_SCANCODE_D))
			(*(t_base **)obj)->origin.origin.x += 0.1;
		if (key_old(*data, SDL_SCANCODE_W))
			(*(t_base **)obj)->origin.origin.z += 0.1;
		if (key_old(*data, SDL_SCANCODE_S))
			(*(t_base **)obj)->origin.origin.z -= 0.1;
	}
}
