/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_specular.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:35:05 by luwargni          #+#    #+#             */
/*   Updated: 2020/03/07 01:00:05 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"
//sudoripal
static int	set_specular(t_thread *data, int color, t_ray *specobj, float dot)
{
	color = (((int)(((data->obj.light[0].color & 0xFF000000) >> 24) * dot) << 24) +
			((int)(((data->obj.light[0].color & 0xFF0000) >> 16) * dot) << 16) +
			((int)(((data->obj.light[0].color & 0xFF00) >> 8) * dot) << 8) +
			((int)(((data->obj.light[0].color & 0xFF) >> 0) * dot) << 0) +
			((int)(((((t_base *)specobj)->effect.color & 0xFF000000) >> 24) * (1.0 - dot)) << 24) +
			((int)(((((t_base *)specobj)->effect.color & 0xFF0000) >> 16) * (1.0 - dot)) << 16) +
			((int)(((((t_base *)specobj)->effect.color & 0xFF00) >> 8) * (1.0 - dot)) << 8) +
			((int)(((((t_base *)specobj)->effect.color & 0xFF) >> 0) * (1.0 - dot)) << 0));
	return (color);
}

int		create_specular(t_thread *data, int color, t_ray *r, float dot)
{
	if (dot >= 0.98 && dot <= 0.9998)
	{
		dot -= 0.98;
		dot = dot * (1.0 / 0.0198);
		if ((((t_base *)r->obj)->effect.type) == PLAN)
			color = set_specular(data, color, r->obj, dot);
		else if ((((t_base *)r->obj)->effect.type) == SPHERE)
			color = set_specular(data, color, r->obj, dot);
		else if ((((t_base *)r->obj)->effect.type) == CONE)
			color = set_specular(data, color, r->obj, dot);
		else if ((((t_base *)r->obj)->effect.type) == TRIANGLE)
			color = set_specular(data, color, r->obj, dot);
		else if ((((t_base *)r->obj)->effect.type) == CYLINDER)
			color = set_specular(data, color, r->obj, dot);
	}
	else if (dot > 0.9998)
		color = data->obj.light[data->obj.index[2]].color;
	return (color);
}
