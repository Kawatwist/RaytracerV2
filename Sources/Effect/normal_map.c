/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:13:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/12 05:28:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static t_point	convert_normalrgb(t_point normal, unsigned char *color,
					float percent)
{
	t_point	base;
	t_point	ret;
	t_point	rot;

	/** Not Bad **/
	base = normalize(normal);
	ret = normalize(div_vec2(fill_vec(color[0], color[1], color[2]), 255.0));
	(void)percent;
	if (ret.y != base.y && ret.z != base.z)
	{
		rot.x = (ang(acos(dot_product(fill_vec(0, ret.y, ret.z),
			fill_vec(0, base.y, base.z)))));
		normal = rotx(normal, rot.x);
		ret = rotx(ret, rot.x);
	}
	if (ret.x != base.x && ret.z != base.z)
	{
		rot.y = (ang(acos(dot_product(fill_vec(ret.x, 0, ret.z),
			fill_vec(base.x, 0, base.z)))));
		normal = roty(normal, rot.y);
		ret = rotx(ret, rot.y);
	}
	if (ret.x != base.x && ret.y != base.y)
	{
		rot.z = (ang(acos(dot_product(fill_vec(ret.x, ret.y, 0),
			fill_vec(base.x, base.y, 0)))));
		normal = rotz(normal, rot.z);
	}
	return (normal);
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
	else if ((((t_sphere *)obj)->effect.type) == OBJ)
		uv = texture_obj(&data, obj, collide, 0);
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
		((t_base *)obj)->effect.normal / 260.0);
	return (normalize(normal));
}
