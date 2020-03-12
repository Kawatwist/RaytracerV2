/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 01:59:04 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/12 02:13:20 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		mv_obj(t_data *data, t_obj **obj)
{
	int		pressed;

	pressed = 0;
	if (key_old(*data, SDL_SCANCODE_A))
	{
		(*obj)->low.x -= 0.1;
		(*obj)->high.x -= 0.1;
		pressed = 1;
	}
	if (key_old(*data, SDL_SCANCODE_D))
	{
		(*obj)->low.x += 0.1;
		(*obj)->high.x += 0.1;
		pressed = 1;
	}
	if (key_old(*data, SDL_SCANCODE_SPACE))
	{
		(*obj)->low.y -= 0.1;
		(*obj)->high.y -= 0.1;
		pressed = 1;
	}
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
	{
		(*obj)->low.y += 0.1;
		(*obj)->high.y += 0.1;
		pressed = 1;
	}
	if (key_old(*data, SDL_SCANCODE_S))
	{
		(*obj)->low.z -= 0.1;
		(*obj)->high.z -= 0.1;
		pressed = 1;
	}
	if (key_old(*data, SDL_SCANCODE_W))
	{
		(*obj)->low.z += 0.1;
		(*obj)->high.z += 0.1;
		pressed = 1;
	}
	if (pressed)
		(*obj)->diff = fill_vec((*obj)->high.x - (*obj)->low.x, (*obj)->high.y - (*obj)->low.y, (*obj)->high.z - (*obj)->low.z);
}
