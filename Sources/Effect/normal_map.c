/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:13:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/13 18:14:31 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the Future Function About Normal
*/

#include "rt.h"

t_point		find_normal_texture(t_data data, void *obj,
		t_vec collide, t_point normal)
{
	int				info;
	unsigned int	index;
	t_point			uv;
	t_point 		normal2;

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
	uv.x = uv.x + (((t_sphere *)obj)->effect.flag & MV ? ((float)(data.percent / 100.0) * (info & 0xFFFF)) : 0);
	while (uv.x < 0.0 || uv.x >= (info & 0xFFFF))
		uv.x += (uv.x < 0 ? (info & 0xFFFF) - 1 : -(info & 0xFFFF) - 1);
	while (uv.y < 0.0 || uv.y >= (data.normal[info >> 16])->h)
		uv.y += (uv.y < 0 ? (data.normal[info >> 16])->h - 1 : -(data.normal[info >> 16])->h) - 1;
	index = (uv.x + (uv.y * (info & 0xFFFF))) * 4;
	normal2.x = (((((unsigned char)(data.normal[info >> 16]->data[index + 1]) / 0x7F) - 0.5) * ((t_base*)obj)->effect.normal / 255.0));
	normal2.y = (((((unsigned char)(data.normal[info >> 16]->data[index + 2]) / 0x7F) - 0.5) * ((t_base*)obj)->effect.normal / 255.0));
	normal2.z = 2;
	return (normal2);
}
