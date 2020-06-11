/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ray_effect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:15:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/11 18:29:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

t_vec		setup_refraction(t_thread *data, void *obj,
		t_vec ray, float dist)
{
	t_vec tmp;

	tmp.origin = set_neworigin_op(ray, dist);
	tmp.direction = find_refraction(*data, obj, ray);
	return (tmp);
}

t_vec		setup_opacity(t_thread *data, void *obj,
		t_vec ray, float dist)
{
	t_vec tmp;

	(void)data;
	(void)obj;
	tmp.origin = set_neworigin_op(ray, dist);
	tmp.direction = veccpy(ray.direction);
	return (tmp);
}

t_vec		setup_reflection(t_thread *data, void *obj,
		t_vec ray, float dist)
{
	t_vec tmp;

	tmp.origin = set_neworigin_neg(ray, dist);
	tmp.direction = veccpy(ray.direction);
	tmp.direction = find_reflexion(obj, tmp, *data);
	return (tmp);
}
