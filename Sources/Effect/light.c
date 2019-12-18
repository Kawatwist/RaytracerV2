
#include "rt.h"

// float		new_set_angle2(t_data data,
// 		void *object, t_light *light, t_vec collide)
// {
// 	int		i;
// 	int		close;
// 	float	currcoef;
// 	t_point	normal;

// 	i = 0;
// 	close = 0;
// 	currcoef = 0;
// 	normal = find_normal(object, collide);
// 	if ((((t_sphere *)object)->effect.normal))
// 		normal = find_normal_texture(data, object, collide, normal);
// 	while (i < 3)
// 	{
// 		currcoef += (1 - (get_dot_abs(normalize(sub_vec(light[i].origin,
// 			collide.origin)), normalize(normal))));
// 		i++;
// 	}
// 	return (currcoef);
// }

// void		new_set_angle(void *object, t_light *light, t_vec collide, float *coef, t_data data)
// {
// 	int			i;
// 	float	curr_coef;
// 	t_point	normal;

// 	curr_coef = 0;
// 	normal = find_normal(object, collide);
// 	if ((((t_sphere *)object)->effect.type & 0xFF) == PLAN)
// 		normal = neg_norm(normal);
// 	if ((((t_sphere *)object)->effect.texture & 0xFF00))
// 		normal = find_normal_texture(data, object, collide, normal);
// 	i = 0;
// 	while (i < 1)
// 	{
// 		curr_coef += (dot_product(normalize(sub_vec(light[i].origin,
// 			collide.origin)), normal));
// 		i++;
// 	}
// 	*coef *= (curr_coef);
// 	if (*coef < 0)
// 		*coef = 0;
// 	if (*coef > 1)
// 		*coef = 1;
// }

// int			find_closer_light(t_data data, t_vec collide, t_light *light, float *coef)
// {
// 	int			nb;
// 	int			basic_color;
// 	float		dist;
// 	void		*obj;

// 	nb = 1;
// 	*coef = 0.7;
// 	basic_color = 0x0;
// 	while (nb--)
// 	{
// 		collide.direction = normalize(sub_vec(light[nb].origin, collide.origin));
// 		obj = find_object(data, data.obj.item, collide, &dist);
// 		if (fabs(length(sub_vec(collide.origin, light[nb].origin))
// 			/ light[nb].distance) < 1 && (fabs(length(sub_vec(collide.origin, light[nb].origin))
// 			/ light[nb].distance) < dist || dist == -1))
// 		{
// 			*coef -= 1.0 - (fabs(length(sub_vec(collide.origin, light[nb].origin)) / light[nb].distance));
// 			if (basic_color != 0x0)
// 				basic_color = set_color(basic_color,
// 				light[nb].color, ((1 - fabs(length(sub_vec(collide.origin, light[nb].origin))
// 				/ light[nb].distance)) / 1.0) * light[nb].intensity);
// 			else
// 				basic_color = set_color(0x0, light[nb].color,
// 					((1 - fabs(length(sub_vec(collide.origin,
// 					light[nb].origin)) / light[nb].distance))
// 					/ 1.0) * light[nb].intensity);
// 		}
// 		else if (dist != -1)
// 			if ((((t_sphere *)obj)->effect.opacity & 0xFF00))
// 				basic_color = set_color(basic_color, ((t_sphere *)obj)->effect.color, 
// 				(((((t_sphere *)obj)->effect.opacity & 0xFF00) >> 8) / 255.0));
// 	}
// 	*coef > 1 ? *coef = 1 : 0;
// 	*coef < 0 ? *coef = 0 : 0;
// 	*coef = 1 - (*coef);
// 	return (basic_color);
// }

// unsigned int	set_light_volume(t_data data,
// 		t_vec ray, t_point light, float *coef)
// {
// 	float			volume;
// 	int				i;
// 	float			len;

// 	ray.direction = sub_vec(light, ray.origin);
// 	len = length(ray.direction);
// 	ray.direction = normalize(ray.direction);
// 	i = 0;
// 	*coef = 0;
// 	while (data.obj.item[i])
// 	{
// 		volume = (data.dist[(((t_sphere *)data.obj.item[i])->effect.type
// 			& 0xFF) - 1](data.obj.item[i], ray));
// 		if (volume > 0)
// 		{
// 			if (volume < len && *coef < (volume / len))
// 			{
// 				*coef = fabsf(*coef) + fabsf(volume / len);
// 				if (*coef > 1.0)
// 					*coef = 1.0;
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }
