/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:59:41 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/29 13:50:08 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void	change_point(float *p1, float *p2, float *p3, float value)
{
	*p1 += value;
	*p2 += value;
	*p3 += value;
}

void		mv_triangle(t_data *data, t_triangle **obj)
{
	if (key_hold(data, SDL_SCANCODE_SPACE))
		change_point(&(*obj)->p1.origin.y, &(*obj)->p2.origin.y,
			&(*obj)->p3.origin.y, -0.1);
	if (key_hold(data, SDL_SCANCODE_LSHIFT))
		change_point(&(*obj)->p1.origin.y, &(*obj)->p2.origin.y,
			&(*obj)->p3.origin.y, 0.1);
	if (key_hold(data, SDL_SCANCODE_A))
		change_point(&(*obj)->p1.origin.x, &(*obj)->p2.origin.x,
			&(*obj)->p3.origin.x, -0.1);
	if (key_hold(data, SDL_SCANCODE_D))
		change_point(&(*obj)->p1.origin.x, &(*obj)->p2.origin.x,
			&(*obj)->p3.origin.x, 0.1);
	if (key_hold(data, SDL_SCANCODE_W))
		change_point(&(*obj)->p1.origin.z, &(*obj)->p2.origin.z,
			&(*obj)->p3.origin.z, -0.1);
	if (key_hold(data, SDL_SCANCODE_S))
		change_point(&(*obj)->p1.origin.z, &(*obj)->p2.origin.z,
			&(*obj)->p3.origin.z, 0.1);
}
