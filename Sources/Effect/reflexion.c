/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:23:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/09 18:19:50 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

t_point		find_reflexion(void *obj, t_vec ray, t_thread data)
{
	float	dot;
	t_point	normal;
	t_point	ret;

	normal = normalize(find_normal_with_txt(data, obj, ray));
	dot = dot_product(ray.direction, normal);
	ret = add_vec(mult_vec2(normal, -2 * dot), ray.direction);
	return (ret);
}
