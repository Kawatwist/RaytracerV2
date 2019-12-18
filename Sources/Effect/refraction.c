#include "rt.h"

t_point		find_refraction(void *obj, t_vec ray)
{
	float	indice;
	float	angle;
	t_point	normal;
	t_point	ret;

	normal = find_normal(obj, ray);
	indice = 2;
	angle = dot_product(ray.direction, normal);
	ret.x = ray.direction.x * indice - normal.x * (-angle + indice * angle);
	ret.y = ray.direction.y * indice - normal.y * (-angle + indice * angle);
	ret.z = ray.direction.z * indice - normal.z * (-angle + indice * angle);
	return (normalize(ret));
}

float		square(float f)
{
	return (f * f);
}