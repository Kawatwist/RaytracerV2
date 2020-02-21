/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:13:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/19 12:37:23 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static t_point	convert_normalrgb(t_point normal, unsigned char *color,
					float percent)
{
	t_point	ret;


	// ret = normalize(div_vec2(fill_vec(color[1], color[2], -color[3]), 255.0));
	// ret = normalize(add_vec(normal, mult_vec2(ret,
	// 	dot_product(normal, normalize(ret)) * (percent / 2.0))));

/** Not Bad **/

	ret = normalize(div_vec2(fill_vec(color[1], color[2], color[3]), 255.0));
	ret = normalize(add_vec(normal, mult_vec2(neg_norm(ret),
		dot_product(normal, normalize(ret)) * (percent / 2.0))));
	return (ret);
}

static t_point	get_uv(t_thread data, void *obj,
					t_vec collide)
{
	t_point uv;

	if (((t_sphere *)obj)->effect.type == PLAN ||
		((t_sphere *)obj)->effect.type == TRIANGLE)
		uv = texture_plan(&data, obj, collide, 0);
	else if ((((t_sphere *)obj)->effect.type) == SPHERE)
		uv = texture_sphere(&data, obj, collide, 0);
	else
		uv = (((t_sphere *)obj)->effect.type) == CONE ?
			texture_cone(&data, obj, collide, 0) :
			texture_cylinder(&data, obj, collide, 0);
	return (uv);
}

t_point			find_normal_texture(t_thread data, void *obj,
					t_vec collide, t_point normal)
{
	int				info;
	t_point			uv;

	uv = get_uv(data, obj, collide);
	info = (((t_base *)obj)->effect.id_normal) << 16;
	info += (data.normal[(info >> 16)]->w & 0xFFFF);
	uv.x = uv.x + (((t_sphere *)obj)->effect.flag & MV ?
		((float)(data.percent / 100.0) * (info & 0xFFFF)) : 0);
	while (uv.x < 0.0 || uv.x >= (info & 0xFFFF))
		uv.x += (uv.x < 0 ? (info & 0xFFFF) :
			-(info & 0xFFFF));
	while (uv.y < 0.0 || uv.y >= (data.normal[(info >> 16)])->h)
		uv.y += (uv.y < 0 ? (data.normal[(info >> 16)])->h :
			-(data.normal[(info >> 16)])->h);
	normal = convert_normalrgb(normal, (unsigned char *)
		((Uint32*)&(data.normal[(info >> 16)]->data[(((int)uv.x +
		((int)uv.y * (info & 0xFFFF))) << 2) + 3])),
		((t_base *)obj)->effect.normal / 255.0);
	return (normalize(normal));
}
