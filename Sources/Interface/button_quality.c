/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_quality.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:26:13 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/22 23:55:07 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_quality(t_data *data, int val)
{
	if (data->flag.pixel == val)
		data->flag.pixel = 0;
	else
		data->flag.pixel = val;
}

void	button_quality(t_data *data)
{
	data->all_button[3].pf = &boo_value_quality;
	data->all_button[3].to_print = "Quality";
	data->all_button[3].val = data->flag.pixel;
	data->all_button[3].i = 3;
}
