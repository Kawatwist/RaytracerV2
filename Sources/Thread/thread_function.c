/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:16:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/26 15:01:15 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point	find_dir(t_thread *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	return (ret);
}

static void		setup_ray(t_thread *data, int x, int y)
{
	data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
	data->ray.direction = normalize(find_dir(data, x, y));
}

void	*thread_function(void *arg)
{
	t_thread 		*data;
	int				x;
	int				y;
	int				curr;

	data = arg;
	curr = -1;
	while (++curr < data->len)
	{
		y = (curr / data->y) + (data->pos / data->x);
		x = curr % data->x;
		if (!(x % ((data->flag.pixel * 2) + 1)) && !(y % ((data->flag.pixel * 2) + 1)))
		{
			setup_ray(data, x, y);
			((unsigned int *)data->pxl)[curr] = send_ray(data, data->ray, data->bounce);
		}
		else
		{
			while ((x % ((data->flag.pixel * 2) + 1) || (y % ((data->flag.pixel * 2) + 1))) && curr < data->len && y == (curr / data->y) + (data->pos / data->x))
			{
				if (y > 0)
					((unsigned int *)data->pxl)[curr] = ((unsigned int *)data->pxl)[curr - (x % ((data->flag.pixel * 2) + 1) + ((y % ((data->flag.pixel * 2) + 1) * data->x)))];
				else
				{
					setup_ray(data, x, y);
					((unsigned int *)data->pxl)[curr] = send_ray(data, data->ray, data->bounce);
				}
				if (x % (data->flag.pixel * 2) + 1)
					curr += 1;
				else
					break;
				x = curr % data->x;
			}
			curr--;
		}
	}
	return (arg);
}
