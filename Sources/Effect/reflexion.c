/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:23:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 18:06:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

t_point		find_reflexion(t_vec ray, t_thread *data)
{
	float	dot;
	t_point	normal;
	t_point	ret;

	normal = veccpy(data->tmp_normal);
	dot = dot_product(ray.direction, normal);
	ret = add_vec(mult_vec2(normal, -2 * dot), ray.direction);
	return (ret);
}
