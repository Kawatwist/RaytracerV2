/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 22:27:14 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/07 00:01:53 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	filter_check(t_data *data, unsigned int i, int j)
{
	while (++i < data->window.x * data->window.y)
	{
		((unsigned int *)data->window.pxl)[i] =
		(((unsigned int *)data->window.pxl)[i] & (0xFF << (j * 8)));
	}
}
