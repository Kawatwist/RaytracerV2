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

(void)base;
    index = -1;
	color = 0x0;
	currcoef = 0.0;
	*coef = 0.0;
	ray.direction = neg_norm(ray.direction);
	while (++index < data->obj.nb_light)
	{
		ang = (1.0 + -dot_product(ray.direction, normalize(sub_vec(ray.origin, data->obj.light[index].origin)))) / 2.0;
		len = length(sub_vec(ray.origin, data->obj.light[index].origin));
		currcoef = ang;
		color = light_color(color, 0x0, 1.0 - currcoef);
		color = light_color(color, data->obj.light[index].color, currcoef);
		// if (ang > 0.5 || ((data->obj.light[index].distance) - len) < 0)
		// {
		// 	currcoef = ((data->obj.light[index].distance) - len);
		// 	currcoef > 1 ? currcoef = 1 : 0;
		// 	currcoef < 0 ? currcoef = 0 : 0;
		// 	currcoef = (currcoef * ang) * data->obj.light[index].intensity;
		// 	color = light_color(color, data->obj.light[index].color, currcoef);
		// }
		// else
		// {
		// 	currcoef = ((ang));
		// 	currcoef > 1 ? currcoef = 1 : 0;
		// 	currcoef < 0 ? currcoef = 0 : 0;
		// 	// color = set_color(color,data->obj.light[index].color, 1 - currcoef);
		// 	color = set_color(color, 0x0, currcoef);
		// }
		*coef += currcoef;
	}
	*coef > 1 ? *coef = 1 : 0;
	*coef = 1 * data->obj.light[index - 1].intensity;
	return (color);
}