#include "rt.h"

static void preset_cam(t_data *data, int index)
{
	(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).pos.origin, fill_vec(-0.5, -0.5, 1));
	(data->obj.camera[index]).x = fill_vec(1.0 / data->window.xscreen, 0, 0);
	(data->obj.camera[index]).y = fill_vec(0, 1.0 / data->window.yscreen, 0);
}

static void apply_rot(t_data *data, t_point base, t_point direction, int index)
{
	t_point		angle;

	if (direction.y != base.y || direction.z != base.z)
	{
		angle.x = ang(acos(dot_product(fill_vec(0, direction.y, direction.z), fill_vec(0, base.y, base.z))));
		(data->obj.camera[index]).sc = add_vec(rotx(sub_vec((data->obj.camera[index]).sc, (data->obj.camera[index]).pos.origin), angle.x), (data->obj.camera[index]).pos.origin);
		(data->obj.camera[index]).x = rotx((data->obj.camera[index]).x, angle.x);
		(data->obj.camera[index]).y = rotx((data->obj.camera[index]).y, angle.x);
		base = rotx(base, angle.x);
	}
	if (direction.x != base.x || direction.y != base.y)
	{
		angle.y = ang(acos(dot_product(fill_vec(direction.x, 0, direction.z), fill_vec(base.x, 0, base.z))));
		(data->obj.camera[index]).sc = add_vec(roty(sub_vec((data->obj.camera[index]).sc, (data->obj.camera[index]).pos.origin), angle.y), (data->obj.camera[index]).pos.origin);
		(data->obj.camera[index]).x = roty((data->obj.camera[index]).x, angle.y);
		(data->obj.camera[index]).y = roty((data->obj.camera[index]).y, angle.y);
		base = roty(base, angle.y);
	}
	if (direction.x != base.x || direction.y != base.y)
	{
		angle.z = ang(acos(dot_product(fill_vec(direction.x, direction.y, 0), fill_vec(base.x, base.y, 0))));
		(data->obj.camera[index]).sc = add_vec(rotz(sub_vec((data->obj.camera[index]).sc, (data->obj.camera[index]).pos.origin), angle.z), (data->obj.camera[index]).pos.origin);
		(data->obj.camera[index]).x = rotz((data->obj.camera[index]).x, angle.z);
		(data->obj.camera[index]).y = rotz((data->obj.camera[index]).y, angle.z);
	}
}

int	initialize_cam(t_data *data)
{
	int	index;
	t_point 		direction;
	t_point 		base;

	index = 0;
	while (index < data->obj.nb_camera)
	{
		direction = normalize((data->obj.camera[index]).pos.direction);
		// printf("%f || %f || %f\n", direction.x, direction.y, direction.z);
		base = fill_vec(0, 0, 1);
		preset_cam(data, index);
		apply_rot(data, base, direction, index);
		index++;
	}
	return (0);
}