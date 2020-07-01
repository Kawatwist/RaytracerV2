/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 15:37:54 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/16 16:25:54 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cartoon(t_data *data, unsigned int i, int tr, int tg)
{
	while (++i < (data->window.x - 1) * (data->window.y - 1))
	{
		tr = (((unsigned char *)data->window.pxl)[(i << 2) + 2] -
			((((unsigned char *)data->window.pxl)[((i + 1) << 2) + 2])));
		tg = (((unsigned char *)data->window.pxl)[(i << 2) + 2] -
			((((unsigned char *)data->window.pxl)[((i +
				data->window.x) << 2) + 2])));
		if (tr > 32 || tr < -32 || tg > 32 || tg < -32)
			((unsigned int *)data->window.pxl)[i] = 0xFF000000;
		tr = (((unsigned char *)data->window.pxl)[(i << 2) + 1] -
			((((unsigned char *)data->window.pxl)[((i + 1) << 2) + 1])));
		tg = (((unsigned char *)data->window.pxl)[(i << 2) + 1] -
			((((unsigned char *)data->window.pxl)[((i +
				data->window.x) << 2) + 1])));
		if (tr > 32 || tr < -32 || tg > 32 || tg < -32)
			((unsigned int *)data->window.pxl)[i] = 0xFF000000;
		tr = (((unsigned char *)data->window.pxl)[i << 2] -
			((((unsigned char *)data->window.pxl)[(i + 1) << 2])));
		tg = (((unsigned char *)data->window.pxl)[i << 2] -
			((((unsigned char *)data->window.pxl)[(i + data->window.x) << 2])));
		if (tr > 32 || tr < -32 || tg > 32 || tg < -32)
			((unsigned int *)data->window.pxl)[i] = 0xFF000000;
	}
}
