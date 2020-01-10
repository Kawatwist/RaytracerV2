#include "rt.h"

t_point		find_reflexion(void *obj, t_vec ray, t_data data)
{
	float	dot;
	t_point	normal;
	t_point	ret;

	(void)data;
	normal = normalize(find_normal_with_txt(data, obj, ray));
	dot = dot_product(ray.direction, normal);
	ret.x = ((normal.x * -2) * dot) + ray.direction.x;
	ret.y = ((normal.y * -2) * dot) + ray.direction.y;
	ret.z = ((normal.z * -2) * dot) + ray.direction.z;
	return (ret);
}