#include "rt.h"

static	t_point	find_dir(t_data *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera->sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera->x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera->y, y));
	ret = sub_vec(ret, data->obj.camera->pos.origin);
	return (ret);
}

int			start_ray(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < data->window.xscreen)
	{
		y = -1;
		while (++y < data->window.yscreen)
		{
			data->ray.origin = veccpy(data->obj.camera->pos.origin);
			data->ray.direction = normalize(find_dir(data, x, y));
			((unsigned int *)data->window.pxl)[x + (y * data->window.xscreen)] = send_ray(data, data->ray, 1);
		}
	}
	return (0);
}
