/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diapo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:38:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/18 17:01:29 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <thread.h>

unsigned int	diapo(t_thread *data, t_vec ray, int index, int bounce)
{
	void			*obj;
	float			dist;
	float			max_dist;
	unsigned int	color;

	max_dist = length(sub_vec(data->obj.light[index].origin, ray.origin));
	obj = check_object_light(data, ray, &dist, max_dist);
	if (!obj || bounce <= 0 || (((t_base *)obj)->effect.opacity) == 0 || dist == -1)
		return (0xFFFFFF);
	ray.origin = set_neworigin_op(ray, dist);
	color = find_color(data, obj, ray);
	// return (color);
	if (0xFFFFFF != diapo(data, ray, index, bounce - 1)) // Probleme Memoire maybe
		printf("%#x\n", diapo(data, ray, index, bounce - 1));
	return (light_color(color, diapo(data, ray, index, bounce - 1)));
}
