/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_specular.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:35:05 by luwargni          #+#    #+#             */
/*   Updated: 2020/03/09 23:02:26 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int	set_specular(t_thread *data, int color, unsigned int specobj, float dot)
{
	color = (((int)(((data->obj.light[0].color & 0xFF000000) >> 24) * dot) << 24) +//surement pas bon
			((int)(((data->obj.light[0].color & 0xFF0000) >> 16) * dot) << 16) +//surement pas bon
			((int)(((data->obj.light[0].color & 0xFF00) >> 8) * dot) << 8) +//surement pas bon
			((int)(((data->obj.light[0].color & 0xFF) >> 0) * dot) << 0) +//surement pas bon
			((int)(((specobj & 0xFF000000) >> 24) * (1.0 - dot)) << 24) +
			((int)(((specobj & 0xFF0000) >> 16) * (1.0 - dot)) << 16) +
			((int)(((specobj & 0xFF00) >> 8) * (1.0 - dot)) << 8) +
			((int)(((specobj & 0xFF) >> 0) * (1.0 - dot)) << 0));
	return (color);
}

int			create_specular(t_thread *data, int color, t_ray *r, float dot)
{
	if (dot >= 0.98 && dot <= 0.9998)
	{
		dot -= 0.98;
		dot = dot * (1.0 / 0.0198);
		if ((((t_base *)r->obj)->effect.type) == PLAN)
			color = set_specular(data, color, r->color[0], dot);
		else if ((((t_base *)r->obj)->effect.type) == SPHERE)
			color = set_specular(data, color, r->color[0], dot);
		else if ((((t_base *)r->obj)->effect.type) == CONE)
			color = set_specular(data, color, r->color[0], dot);
		else if ((((t_base *)r->obj)->effect.type) == TRIANGLE)
			color = set_specular(data, color, r->color[0], dot);
		else if ((((t_base *)r->obj)->effect.type) == CYLINDER)
			color = set_specular(data, color, r->color[0], dot);
	}
	else if (dot > 0.9998)
		color = data->obj.light[data->obj.index[2]].color;//surement pas bon
	return (color);
}
