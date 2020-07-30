/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diapo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:38:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/30 14:39:51 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <thread.h>

unsigned int	diapo(t_thread *data, t_vec *ray, int index, int bounce)
{
	void			*obj;
	float			dist;
	float			max_dist;
	unsigned int	color;
	unsigned int	new_color;

	max_dist = length(sub_vec(data->obj.light[index].origin, ray->origin));
	obj = check_object(data, *ray, &dist, NULL);
	if (!obj || bounce <= 0 || ((t_base *)obj)->effect.opacity == 0
	|| dist > max_dist)
		return (0xFFFFFF);
	ray->origin = set_neworigin_op(*ray, dist);
	color = find_color(data, obj, *ray);
	new_color = diapo(data, ray, index, bounce - 1);
	return (light_color(color, new_color));
}
