/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quality.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:04:18 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/06 21:18:05 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

void			quality(t_thread *data, int *x, int *y, int *curr)
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
