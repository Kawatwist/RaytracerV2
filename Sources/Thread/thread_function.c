/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:16:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/18 13:14:29 by lomasse          ###   ########.fr       */
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

static t_vec		setup_ray(t_thread *data, int x, int y)
{
	data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
	data->ray.direction = normalize(find_dir(data, x, y));
	return (data->ray);
}

static void			quality(t_thread *data, int *x, int *y, int *curr)
{
	while ((*x % ((data->flag.pixel * 2) + 1) || (*y % ((data->flag.pixel * 2)
			+ 1))) && *curr < data->len && *y == (*curr / data->x) +
			(data->pos / data->x))
	{
		if (*curr < data->x * ((data->flag.pixel * 2) + 1) || *y < (*y %
			((data->flag.pixel * 2) + 1)))
			((unsigned int *)data->pxl)[*curr] = ((unsigned int *)data->pxl)
				[*x - (*x % ((data->flag.pixel * 2) + 1))];
		else
			((unsigned int *)data->pxl)[*curr] = ((unsigned int *)data->pxl)
				[*curr - (*x % ((data->flag.pixel * 2) + 1) + ((*y %
					((data->flag.pixel * 2) + 1) * data->x)))];
		if (*x % (data->flag.pixel * 2) + 1)
			*curr += 1;
		else
			break ;
		*x = *curr % data->x;
	}
	*curr -= 1;
}

static void			basic_render(t_thread *data, int *x, int *y, int *curr)
{
	*y = (*curr / data->x) + (data->pos / data->x);
	*x = *curr % data->x;
	if (*curr < data->x || (!(*x % ((data->flag.pixel * 2) + 1)) && !(*y %
			((data->flag.pixel * 2) + 1))))
		((unsigned int *)data->pxl)[*curr] = send_ray(data, setup_ray(data, *x,
				*y), data->bounce);
	else
		quality(data, x, y, curr);
}

void	*thread_function(void *arg)
{
	t_thread 		*data;
	int				x;
	int				y;
	int				curr;

	data = arg;
	curr = -1;
	if (data->flag.antialiasing == 0)
	{
		while (++curr < data->len)
			basic_render(data, &x, &y, &curr);
	}
	else
	{
		while (++curr < data->len)
			aa_render(data, &x, &y, &curr);
	}
	return (arg);
}
