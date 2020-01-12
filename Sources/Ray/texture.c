#include "rt.h"

int			find_size(t_data data, void *obj, int choose)
{
	int index;

	if (choose != 0)
	{
		index = (((t_sphere *)obj)->effect.id_texture);
		return (((data.texture[index])->w << 16) + (data.texture[index])->h);
	}
	else
	{
		index = (((t_sphere *)obj)->effect.id_normal);
		return (((data.normal[index])->w << 16) + (data.normal[index])->h);
	}
}


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

t_point		texture_plan(t_data *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	t_point ontexture;
	t_point u;
	t_point v;

	wh = find_size(*data, obj, choose);
	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z, -((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	ontexture.y = dot_product(ray.origin, u) * (wh & 0xFFFF);
	ontexture.x = dot_product(ray.origin, v) * (wh >> 16);
	while (ontexture.x < 0 || ontexture.x >= (wh >> 16))
		ontexture.x += (ontexture.x < 0 ? (wh >> 16) - 1 : -(wh >> 16) - 1);
	while (ontexture.y < 0 || ontexture.y >= (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) - 1 : -(wh & 0xFFFF) - 1);
	return (ontexture);
}

t_point		texture_sphere(t_data *data, void *obj, t_vec ray, int choose)
{
	t_point	ontexture;
	int		wh;
	float	phi;
	float	theta;

	wh = find_size(*data, obj, choose);
	theta = acos(sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).y / ((t_sphere *)obj)->rayon);
	phi = atan2(sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = (int)(((wh & 0xFFFF) - 1) * ((M_PI - theta) / (M_PI)));
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ? (wh & 0xFFFF0000) >> 16 : -((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	return (ontexture);
}

t_point		texture_cylinder(t_data *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	float	phi;
	t_point ontexture;
	t_point	u;
	t_point	v;

	wh = find_size(*data, obj, choose);
	u = fill_vec(((t_cylinder *)obj)->origin.direction.y, ((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_base *)obj)->origin.direction);
	phi = atan2(sub_vec(ray.origin, ((t_base *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_base *)obj)->origin.origin).x);
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = ((float)((int)ray.origin.y) - ray.origin.y) * (wh & 0xFFFF);
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ? (wh & 0xFFFF0000) >> 16 : -((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	return (ontexture);
}

t_point		texture_cone(t_data *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	t_point ontexture;
	t_point	u;
	float	phi;

	wh = find_size(*data, obj, choose);
	u = fill_vec(((t_cylinder *)obj)->origin.direction.y, ((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	phi = atan2(sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = ((float)((int)ray.origin.y) - ray.origin.y) * (wh & 0xFFFF);
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ? (wh & 0xFFFF0000) >> 16 : -((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	return (ontexture);
}