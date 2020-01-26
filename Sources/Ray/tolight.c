/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolight.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:37 by lomasse           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2020/01/15 23:06:08 by luwargni         ###   ########.fr       */
=======
/*   Updated: 2020/01/16 00:55:15 by lomasse          ###   ########.fr       */
>>>>>>> bf594b0eec291cb4f467f4a85a9653fd6931d85e
=======
/*   Updated: 2020/01/24 22:27:46 by lomasse          ###   ########.fr       */
>>>>>>> ec204c001aceed3ca63f4e18db94dcd8b8b39a69
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static unsigned int	add_color(unsigned int base, unsigned int new)
{
	unsigned char	color[4];

	color[3] = 0xFF;
	color[2] = (((base & 0xFF0000) >> 16)) + (((new & 0xFF0000) >> 16)) > 255
			? 255 : (((base & 0xFF0000) >> 16)) + (((new & 0xFF0000) >> 16));
	color[1] = (((base & 0xFF00) >> 8)) + (((new & 0xFF00) >> 8)) > 255 ? 255
			: (((base & 0xFF00) >> 8)) + (((new & 0xFF00) >> 8));
	color[0] = ((base & 0xFF)) + ((new & 0xFF)) > 255 ? 255 : ((base & 0xFF))
			+ ((new & 0xFF));
	return (*((int *)color));
}

static int			light_color(unsigned int color, unsigned int newcolor)
{
	unsigned char	value[4];
	int				tmp;

	if ((((newcolor & 0xFF) * (color & 0xFF)) / 255) > 255)
		value[0] = 255;
	else if ((((newcolor & 0xFF) * (color & 0xFF)) / 255) < 0)
		value[0] = 0;
	else
		value[0] = ((newcolor & 0xFF) * (color & 0xFF)) / 255;
	if ((tmp = (((newcolor & 0xFF00) >> 8) *
			((color & 0xFF00) >> 8) / 255)) > 255)
		value[1] = 255;
	else
		value[1] = tmp;
	if ((tmp = (((newcolor & 0xFF0000) >> 16) *
			((color & 0xFF0000) >> 16) / 255)) > 255)
		value[2] = 255;
	else
		value[2] = tmp;
	value[3] = 255;
	return (*(int*)(value));
}

float				stop_light(t_data *data, t_light light, t_vec ray)
{
	float	intersect;
	void	*obj;
	t_vec	check;

	intersect = -1;
	check.origin = veccpy(ray.origin);
	check.direction = normalize(sub_vec(light.origin, ray.origin));
	obj = check_object_light(data, check, &intersect);
	if (obj == NULL || intersect <= 0)
		return (-1);
	return (intersect);
}

static float		dist(t_data *data, t_vec ray, int index, float *obj)
{
	if (obj[1] > 0.0 && !(obj[1] >= length(sub_vec(
		data->obj.light[index].origin, ray.origin))))
		obj[0] = obj[1] / length(sub_vec(data->obj.light[index].origin,
			ray.origin));
	else
		obj[0] = 1;
	return (obj[0]);
}

unsigned int		ray_to_light(t_data *data, t_vec tmp, t_vec ray, int base)
{
	int		color;
	int		index;
	float	obj[2];
	float	len;
	float	dot;

	(void)tmp;
	index = -1;
	color = data->ambiant;
	while (++index < data->obj.nb_light)
	{
		dot = -(((1 - dot_product(normalize(sub_vec(ray.origin,
			data->obj.light[index].origin)),
			normalize(ray.direction))) * -1) / 2.0);
		len = data->obj.light[index].distance - length(sub_vec(ray.origin,
			data->obj.light[index].origin));
		obj[1] = stop_light(data, data->obj.light[index], ray);
		obj[0] = dist(data, ray, index, obj);
		len > 1 ? len = 1 : 0;
		len < 0 ? len = 0 : 0;
		dot *= data->obj.light[index].intensity;
		color = add_color(color, light_color(base, set_color(0,
			data->obj.light[index].color, (dot * len) * obj[0], -1)));
	}
	return (color);
}
