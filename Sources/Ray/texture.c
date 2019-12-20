#include "rt.h"

int			find_size(t_data data, void *obj)
{
	int ret;
	int index;

	index = (((t_sphere *)obj)->effect.id_texture);
	ret = ((data.texture[index])->w << 16) + (data.texture[index])->h;
	return (ret);
}

// t_point		find_normal_texture(t_data data, void *obj,
// 		t_vec collide, t_point normal)
// {
// 	int		info;
// 	t_point	uv;
// 	t_point normal2;

// 	if ((((t_sphere *)obj)->effect.type & 0xFF) == PLAN)
// 		uv = texture_plan(data, obj, collide, 1);
// 	if ((((t_sphere *)obj)->effect.type & 0xFF) == SPHERE)
// 		uv = texture_sphere(data, obj, collide, 1);
// 	uv.x = uv.x + (((t_sphere *)obj)->effect.id_texture &
// 		MV ? data.rotation : 0);
// 	info = (((t_sphere *)obj)->effect.id_texture & (0xFFFF0000 - MV));
// 	info += data.texture[info >> 16]->w;
// 	while (uv.x < 0 || uv.x > (data.texture[info >> 16])->w)
// 		uv.x += (uv.x < 0 ? (data.texture[info >> 16])->w :
// 			-(data.texture[info >> 16])->w);
// 	while (uv.y < 0 || uv.y > (data.texture[info >> 16])->h)
// 		uv.y = uv.y > (data.texture[info >> 16])->h ? 0 : uv.y;
// 	normal2.x = (((((data.texture[info >> 16])->data[(int)(uv.x +
// 		(uv.y * (info & 0xFFFF)))] & 0xFF) / 255.0) * 2) - 1);
// 	normal2.y = ((((((data.texture[info >> 16])->data[(int)(uv.x +
// 		(uv.y * (info & 0xFFFF)))] & 0xFF00) >> 8) / 255.0) * 2) - 1);
// 	normal2.z = ((((((data.texture[info >> 16])->data[(int)(uv.x +
// 		(uv.y * (info & 0xFFFF)))] & 0xFF0000) >> 16) / 255.0) * 2) - 1);
// 	normal = normalize(add_vec(normal, mult_vec2(neg_norm(normal2),
// 		dot_product(normal, normalize(normal2)) * 0.5)));
// 	return (normal);
// }

t_point		texture_plan(t_data *data, void *obj, t_vec ray)
{
	int		wh;
	t_point ontexture;
	t_point u;
	t_point v;

	wh = find_size(*data, obj);
	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z, -((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	ontexture.y = dot_product(ray.origin, u) * (wh & 0xFFFF);
	ontexture.x = dot_product(ray.origin, v) * ((wh & 0xFFFF0000) >> 16);
	while (ontexture.x < 0)
		ontexture.x += ((wh & 0xFFFF0000) >> 16);
	while (ontexture.y < 0)
		ontexture.y += (wh & 0xFFFF);
	return (ontexture);
}

t_point		texture_sphere(t_data *data, void *obj, t_vec ray)
{
	t_point	ontexture;
	int		wh;
	float	phi;
	float	theta;

	wh = find_size(*data, obj);
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

t_point		texture_cylinder(t_data *data, void *obj, t_vec ray)
{
	t_point ontexture;
	t_point	u;
	float	phi;

	(void)data;
	u = fill_vec(((t_cylinder *)obj)->origin.direction.y, ((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	phi = atan2(sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = dot_product(ray.origin, u) * 600;
	ontexture.y = (int)((600 - 1) * ((M_PI - phi) / (M_PI))); // RESIZE ?
	while (ontexture.x < 0 || ontexture.x > 600)
		ontexture.x += (ontexture.x < 0 ? 600 : -600);
	while (ontexture.y < 0 || ontexture.y > 600)
		ontexture.y += (ontexture.y < 0 ? 600 : -600);
	return (ontexture);
}
