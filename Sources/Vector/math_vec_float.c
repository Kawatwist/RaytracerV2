#include "rt.h"

t_point		sub_vec2(t_point v1, float sub)
{
	t_point ret;

	ret.x = v1.x - sub;
	ret.y = v1.y - sub;
	ret.z = v1.z - sub;
	return (ret);
}

t_point		mult_vec2(t_point v1, float mult)
{
	t_point ret;

	ret.x = v1.x * mult;
	ret.y = v1.y * mult;
	ret.z = v1.z * mult;
	return (ret);
}

t_point		div_vec2(t_point v1, float div)
{
	return (fill_vec(v1.x / div, v1.y / div, v1.z / div));
}