/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:27:58 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/06 02:05:37 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point		set_neworigin_neg(t_vec ray, float distance)
{
	ray.origin = add_vec(mult_vec2(normalize(ray.direction),
		(distance - 0.0001)), ray.origin);
	return (ray.origin);
}

t_point		set_neworigin_op(t_vec ray, float distance)
{
	ray.origin = add_vec(mult_vec2(normalize(ray.direction),
		(distance + 0.0001)), ray.origin);
	return (ray.origin);
}

t_point		set_neworigin(t_vec ray, float distance)
{
	t_point tmp;

	ray.direction = normalize(ray.direction);
	tmp = mult_vec2(ray.direction, distance);
	ray.origin = add_vec(tmp, ray.origin);
	return (ray.origin);
}
