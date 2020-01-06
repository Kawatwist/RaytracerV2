#include "rt.h"

static unsigned int	add_color(unsigned int base, unsigned int new)
{
	unsigned char	color[4];

	color[3] = 0xFF;
	color[2] = (((base & 0xFF0000) >> 16)) + (((new & 0xFF0000) >> 16)) > 255 ? 255 : (((base & 0xFF0000) >> 16)) + (((new & 0xFF0000) >> 16));
	color[1] = (((base & 0xFF00) >> 8)) + (((new & 0xFF00) >> 8)) > 255 ? 255 : (((base & 0xFF00) >> 8)) + (((new & 0xFF00) >> 8));
	color[0] = ((base & 0xFF)) + ((new & 0xFF)) > 255 ? 255 : ((base & 0xFF)) + ((new & 0xFF));
	return (*((int *)color));
}

static int		light_color(unsigned int color, unsigned int newcolor)
{
	unsigned char	value[4];
	
	if ((((newcolor & 0xFF) * (color & 0xFF)) / 255) > 255)
		value[0] = 255;
	else if ((((newcolor & 0xFF) * (color & 0xFF)) / 255) < 0)
		value[0] = 0;
	else
		value[0] = ((newcolor & 0xFF) * (color & 0xFF)) / 255;

	if ((((newcolor & 0xFF00) >> 8) * ((color & 0xFF00) >> 8) / 255) > 255)
		value[1] = 255;
	else if (((((newcolor & 0xFF00) >> 8) * ((color & 0xFF00) >> 8)) / 255) < 0)
		value[1] = 0;
	else
		value[1] = (((newcolor & 0xFF00) >> 8) * ((color & 0xFF00) >> 8)) / 255;

	if ((((newcolor & 0xFF0000) >> 16) * ((color & 0xFF0000) >> 16) / 255) > 255)
		value[2] = 255;
	else if (((((newcolor & 0xFF0000) >> 16) * ((color & 0xFF0000) >> 16)) / 255) < 0)
		value[2] = 0;
	else
		value[2] = (((newcolor & 0xFF0000) >> 16) * ((color & 0xFF0000) >> 16)) / 255;

	value[3] = 255;
	return (*(int*)(value));
}

unsigned int	ray_to_light(t_data *data, t_vec ray, int base)
{
	int		color;
	int		index;
	float	len;
	float	dot;

	index = -1;
	color = 0;
	while (++index < data->obj.nb_light)
	{
		dot = -(((1 - -dot_product(normalize(sub_vec(ray.origin, data->obj.light[index].origin)), normalize(ray.direction))) * -1) / 2.0);
		len = data->obj.light[index].distance - length(sub_vec(ray.origin, data->obj.light[index].origin));
		if (len < 0)
			len = 0;
		if (len > 1)
			len = 1;
		color = add_color(color, light_color(base, set_color(0, data->obj.light[index].color, dot * len)));
	}
	return (color);
}