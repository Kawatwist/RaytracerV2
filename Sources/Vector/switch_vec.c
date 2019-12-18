#include "rt.h"

t_point		set_neworigin_neg(t_vec ray, float distance)
{
	ray.origin = add_vec(mult_vec2(normalize(ray.direction),
		(distance - 0.00001)), ray.origin);
	return (ray.origin);
}

t_point		set_neworigin_op(t_vec ray, float distance)
{
	ray.origin = add_vec(mult_vec2(normalize(ray.direction),
		(distance + 0.00001)), ray.origin);
	return (ray.origin);
}

t_point		set_neworigin(t_vec ray, float distance)
{
	ray.origin = add_vec(mult_vec2(normalize(ray.direction),
		(distance)), ray.origin);
	return (ray.origin);
}