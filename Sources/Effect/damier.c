/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 02:34:06 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/09 03:18:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

int				find_damier(t_thread *data, void *obj, t_vec ray)
{
	t_point		u;
	t_point		v;
	t_point		uv;

	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z,
		-((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	uv.x = (unsigned int)((dot_product(ray.origin, v) - 1) * 50);
	uv.y = (unsigned int)((dot_product(ray.origin, u) - 1) * 50);
	if (((unsigned int)uv.x + ((unsigned int)uv.y) + data->percent) % 2)
		return (data->ambiant);
	return (0xFF000000);
}
