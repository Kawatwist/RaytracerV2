#include "rt.h"

static int		light_color(int color, int newcolor, float coef)
{
	int		ret;

	ret	= ((int)((newcolor & 0xFF) * coef) & 0xFF);
	ret	+= ((int)((newcolor & 0xFF00) * coef) & 0xFF00);
	ret	+= ((int)((newcolor & 0xFF0000) * coef) & 0xFF0000);
	ret = ((ret & 0xFF) + (color & 0xFF)) +
			((ret & 0xFF00) + (color & 0xFF00) & 0xFF00) +
			((ret & 0xFF0000) + (color & 0xFF0000) & 0xFF0000);
	return (ret);
}

unsigned int	ray_to_light(t_data *data, t_vec ray, float *coef)
{
	int     index;
	int		color;
	float	currcoef;
	float	ang;
	float	len;

    index = -1;
	color = 0x000000;
	currcoef = 0;
	*coef = 0;
	ray.direction = neg_norm(ray.direction);
	while (++index < data->obj.nb_light)
	{
		ang = -dot_product(ray.direction, sub_vec(ray.origin, data->obj.light[index].origin));
		len = length(sub_vec(ray.origin, data->obj.light[index].origin));
		if (ang > 0.0) // && Pas d'obstacle
		{
			currcoef = (ang);
			currcoef = (currcoef * data->obj.light[index].intensity);
			currcoef > 1 ? currcoef = 1 : 0;
			currcoef < 0 ? currcoef = 0 : 0;
			color += light_color(color, data->obj.light[index].color, currcoef);
			*coef += currcoef;
		}
	}
	*coef > 1 ? *coef = 1 : 0;
	return (color);
}

// unsigned int	ray_to_light(t_data *data, t_vec ray, float *coef)
// {
//     int     index;
// 	int		color;
// 	float	currcoef;

//     index = 0;
// 	color = 0x000000;
// 	currcoef = 0;
// 	*coef = 0;
//     while (index < data->obj.nb_light)
// 	{
// 		if (dot_product(ray.direction, sub_vec(data->obj.light[index].origin, ray.origin)) < 0)
// 		{
// 			// if (check_object(data, ray, &currcoef) == NULL || (currcoef > length(sub_vec(data->obj.light[index].origin, ray.origin)) || currcoef == -1))
// 			// {
// 				currcoef = (-dot_product(ray.direction, sub_vec(data->obj.light[index].origin, ray.origin))) - (-length(sub_vec(data->obj.light[index].origin, ray.origin)) - data->obj.light[index].distance);
// 				currcoef > 1 ? currcoef = 1 : 0;
// 				currcoef < 0 ? currcoef = 0 : 0;
// 				currcoef = (currcoef * data->obj.light[index].intensity);
// 				currcoef > 1 ? currcoef = 1 : 0;
// 				color += light_color(color, data->obj.light[index].color, currcoef);
// 				*coef += currcoef;
// 				// printf("Index : %d\t %f\n", index, currcoef);
// 			// }
// 		}
// 		index++;
// 	}
// 	*coef *= -1;
// 	// *coef > 1 ? *coef = *coef - 1 : 0;
// 	return (color);
// }