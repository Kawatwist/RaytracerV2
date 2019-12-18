#include "rt.h"

t_point		veccpy(t_point pnt)
{
	t_point ret;

	ret.x = pnt.x;
	ret.y = pnt.y;
	ret.z = pnt.z;
	return (ret);
}

t_vec		create_vec(t_point origin, t_point direction)
{
	t_vec 	ret;

	ret.origin = veccpy(origin);
	ret.direction = veccpy(direction);
	return (ret);
}

t_point		fill_vec(float x, float y, float z)
{
	t_point ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}