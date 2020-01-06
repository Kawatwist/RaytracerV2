#include "rt.h"

t_point		mult_vec(t_point v1, t_point v2)
{
	t_point	ret;

	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	return (ret);
}

t_point		div_vec(t_point v1, t_point v2)
{
	t_point	ret;

	ret.x = v1.x / v2.x;
	ret.y = v1.y / v2.y;
	ret.z = v1.z / v2.z;
	return (ret);
}

t_point		add_vec(t_point v1, t_point v2)
{
	t_point ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_point		sub_vec(t_point v1, t_point v2)
{
	t_point ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_point		normalize(t_point v1)
{
	float	value;

	if (!v1.x && !v1.y && !v1.z)
		return (fill_vec(0, 0, 1));
	value = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	return (fill_vec(v1.x / value, v1.y / value, v1.z / value));
}