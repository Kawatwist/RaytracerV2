#include "rt.h"

static int		light_color(int color, int newcolor, float coef)
{
	int				ret;
	unsigned char	value[4];

	coef > 1 ? coef = 1 : 0;
	coef < 0 ? coef = 0 : 0;
	ret	= ((int)((newcolor & 0xFF) * coef) > 255 ? 255 : (int)((newcolor & 0xFF) * coef));
	ret	+= (((int)((newcolor & 0xFF00) * coef) & 0xFF00) >> 8) > 255 ? 0xFF00 : (int)((newcolor & 0xFF00) * coef) & 0xFF00;
	ret	+= (((int)((newcolor & 0xFF0000) * coef) & 0xFF0000) >> 16) > 255 ? 0xFF0000 : (int)((newcolor & 0xFF0000) * coef) & 0xFF0000;
	value[0] = ((ret & 0xFF) + (color & 0xFF) > 255 ? 255 : (ret & 0xFF) + (color & 0xFF));
	value[1] = ((((ret & 0xFF00) + (color & 0xFF00)) >> 8) > 255 ? 255 : ((ret & 0xFF00) + (color & 0xFF00)) >> 8);
	value[2] = ((((ret & 0xFF0000) + (color & 0xFF0000)) >> 16) > 255 ? 255 : ((ret & 0xFF0000) + (color & 0xFF0000)) >> 16);
	value[3] = 255;
	return (*(int*)(value));
}

unsigned int	ray_to_light(t_data *data, t_vec ray, float *coef, int base)
{
	int     index;
	int		color;
	float	currcoef;
	float	ang;
	float	len;

    index = -1;
	color = base;
	currcoef = 0;
	*coef = 0;
	ray.direction = neg_norm(ray.direction);
	while (++index < data->obj.nb_light)
	{
		ang = -dot_product(ray.direction, normalize(sub_vec(ray.origin, data->obj.light[index].origin)));
		len = length(sub_vec(ray.origin, data->obj.light[index].origin));
		if (ang > 0.0 || ((data->obj.light[index].distance) - len) < 0)
		{
			currcoef = ((data->obj.light[index].distance) - len);
			currcoef > 1 ? currcoef = 1 : 0;
			currcoef < 0 ? currcoef = 0 : 0;
			currcoef = (currcoef * ang) * data->obj.light[index].intensity;
			color = light_color(color, data->obj.light[index].color, currcoef);
		}
		else
		{
			currcoef = ((-ang) * 3.0);
			currcoef > 1 ? currcoef = 1 : 0;
			currcoef < 0 ? currcoef = 0 : 0;
			color = set_color(color, 0x0, currcoef);
		}
		*coef += currcoef;
		
	}
	*coef > 1 ? *coef = 1 : 0;
	// *coef = 1;
	return (color);
}