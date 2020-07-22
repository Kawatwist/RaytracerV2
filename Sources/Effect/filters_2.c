/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:09:24 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/22 21:53:33 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	filter_negatif(t_data *data, unsigned int i)
{
	while (++i < data->window.x * data->window.y)
	{
		((unsigned int *)data->window.pxl)[i] *= -1;
	}
}
