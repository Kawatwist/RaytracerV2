/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:27:58 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/13 18:27:59 by lomasse          ###   ########.fr       */
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
	ray.origin = add_vec(mult_vec2(normalize(ray.direction),
		(distance)), ray.origin);
	return (ray.origin);
}
