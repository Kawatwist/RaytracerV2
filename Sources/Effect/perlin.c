#include "rt.h"
#include "thread.h"


static int perlin_color(float val)
{
	int color;

	color = 0xFF000000;
	val = (int)val - val;
	if(val < 0)
		val = -val;
	if (val > 1)
		val = 1;
	color = color + ((int)(val * 255) << 16);
	return (color);
}

static int		perlin_cylinder(t_thread *data, void *obj, t_vec ray)
{
	float	phi;
	t_point ontexture;
	t_point	u;
	t_point	v;

	u = fill_vec(((t_cylinder *)obj)->origin.direction.y,
		((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_base *)obj)->origin.direction);
	phi = atan2(sub_vec(ray.origin, ((t_base *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_base *)obj)->origin.origin).x);
	ontexture.x = (phi / (2 * M_PI));
	ontexture.y = ((float)((int)((t_base *)obj)->origin.origin.y) -
		ray.origin.y) / 100.0;
	return(perlin_color(get_perlin(data->perlin, ontexture)));
}

static int		perlin_sphere(t_thread *data, void *obj, t_vec ray)
{
	t_point	ontexture;
	float	phi;
	float	theta;

	theta = acos(sub_vec(ray.origin,
		((t_sphere *)obj)->origin.origin).y / ((t_sphere *)obj)->rayon);
	phi = atan2(sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = (phi / (2 * M_PI));
	ontexture.y = ((M_PI - theta) / (M_PI));
	return(perlin_color(get_perlin(data->perlin, ontexture)));
}

static int		perlin_plan(t_thread *data, void *obj, t_vec ray)
{
	t_point		u;
	t_point		v;
	t_point		uv;
	
	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z,
		-((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	uv.x = (dot_product(ray.origin, v));
	uv.y = (dot_product(ray.origin, u));
	return (perlin_color(get_perlin(data->perlin, uv)));
}

int				find_perlin(t_thread *data, void *obj, t_vec ray)
{
	if (((t_base *)obj)->effect.type == PLAN)
		return (perlin_plan(data, obj, ray));
	else if (((t_base *)obj)->effect.type == SPHERE)
		return (perlin_sphere(data, obj, ray));
	return (perlin_cylinder(data, obj, ray));
}
