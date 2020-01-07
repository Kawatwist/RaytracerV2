#include "rt.h"

static	t_point	find_dir(t_data *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[0].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[0].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[0].y, y));
	ret = sub_vec(ret, data->obj.camera[0].pos.origin);
	return (ret);
}

static void	low_quality(t_data *data, int *x, int *y)
{
	(void)x;
	(void)y;
	(void)data;
	int		w;
	int		pxl;

	w = 0;
	pxl = 0;
	while (w < data->window.xscreen)
	{
		pxl = 0;
		while (pxl < (data->flag.pixel))
		{
			((unsigned int *)data->window.pxl)[(*x) + ((*y + pxl) * data->window.xscreen) + w] =
				((unsigned int *)data->window.pxl)[*x + ((*y - 1) * data->window.xscreen) + w];
			pxl++;
		}
		w++;
	}
	(*y) += (data->flag.pixel);
}

int			start_ray(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->window.yscreen)
	{
		x = -1;
		while (++x < data->window.xscreen)
		{
			data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
			data->ray.direction = normalize(find_dir(data, x, y));
			((unsigned int *)data->window.pxl)[x + (y * data->window.xscreen)] =
				send_ray(data, data->ray, 1);
			while (x % (data->flag.pixel + 1))
			{
				((unsigned int *)data->window.pxl)[x + 1 + (y * data->window.xscreen)] =
				((unsigned int *)data->window.pxl)[x + (y * data->window.xscreen)];
				x += 1;
			}
		}
		if (data->flag.pixel)
			low_quality(data, &x, &y);
	}
	data->obj.camera[data->obj.index[0]].pos.direction = normalize(find_dir(data, data->window.xscreen >> 1, data->window.yscreen >> 1));
	return (0);
}
