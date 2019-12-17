#include "rt.h"

t_point		cross_vec(t_point v1, t_point v2)
{
	t_point ret;

	ret.x = v1.y * v2.z - v2.y * v1.z;
	ret.y = v1.x * v2.z - v2.x * v1.z;
	ret.z = v1.x * v2.y - v2.x * v1.y;
	return (ret);
}

float		dot_product(t_point v1, t_point v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

float		length(t_point v1)
{
	return (sqrtf((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z)));
}