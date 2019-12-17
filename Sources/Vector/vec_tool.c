#include "rt.h"

t_point		neg_norm(t_point v1)
{
	t_point	ret;

	ret.x = -v1.x;
	ret.y = -v1.y;
	ret.z = -v1.z;
	return (ret);
}

t_point		sqrt_vec(t_point v1)
{
	t_point	ret;

	ret.x = sqrtf(v1.x);
	ret.y = sqrtf(v1.y);
	ret.z = sqrtf(v1.z);
	return (ret);
}