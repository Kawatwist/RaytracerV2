/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:13:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/20 23:55:05 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the Future Function About Normal Mapping
**	It's actually doesnt work correctly
**	Need to be Set back for Rt
*/

#include "rt.h"

static t_point	convert_normalrgb(t_point normal, unsigned char *color, float percent)
{
	t_point	ret;

	ret = normalize(div_vec2(fill_vec(color[1], color[2], color[3]), 255.0));
	ret = normalize(add_vec(normal, mult_vec2(neg_norm(ret),
		dot_product(normal, normalize(ret)) * (percent / 2.0))));
	return (ret);
}

t_point		find_normal_texture(t_data data, void *obj,
					t_vec collide, t_point normal)
{
	int				info;
	unsigned int	index;
	t_point			uv;
	// t_point 		normal2;

	(void)normal;
	if ((((t_sphere *)obj)->effect.type & 0xFF) == PLAN)
		uv = texture_plan(&data, obj, collide, 0);
	else if ((((t_sphere *)obj)->effect.type & 0xFF) == SPHERE)
		uv = texture_sphere(&data, obj, collide, 0);
	else if ((((t_sphere *)obj)->effect.type & 0xFF) == CONE)
		uv = texture_cone(&data, obj, collide, 0);
	else if ((((t_sphere *)obj)->effect.type & 0xFF) == CYLINDER)
		uv = texture_cylinder(&data, obj, collide, 0);
	info = (((t_base *)obj)->effect.id_normal) << 16;
	info += (data.normal[info >> 16]->w & 0xFFFF);
	uv.x = uv.x + (((t_sphere *)obj)->effect.flag & MV ?
		((float)(data.percent / 100.0) * (info & 0xFFFF)) : 0);
/*		No problem before */
	while (uv.x < 0.0 || uv.x >= (info & 0xFFFF))
		uv.x += (uv.x < 0 ? (info & 0xFFFF) :
			-(info & 0xFFFF));
	while (uv.y < 0.0 || uv.y >= (data.normal[info >> 16])->h)
		uv.y += (uv.y < 0 ? (data.normal[info >> 16])->h :
			- (data.normal[info >> 16])->h);
/*		I Don't think before too */
	index = ((int)uv.x + ((int)uv.y * (info & 0xFFFF))) * 4;
/*		This is correct */
	normal = convert_normalrgb(normal, (unsigned char *)((Uint32*)&(data.normal[info >> 16]->data[index + 3])), ((t_base *)obj)->effect.normal / 255.0); // +3 ??
	return (normalize(normal));
}
