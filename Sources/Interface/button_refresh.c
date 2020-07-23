/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_refresh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:34:17 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/22 23:55:05 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_refresh(t_data *data, int val)
{
	if (data->flag.asked == val)
		data->flag.asked = 0;
	else
		data->flag.asked = val;
}

void	button_once_refresh(t_data *data)
{
	data->all_button[0].pf = &boo_value_refresh;
	data->all_button[0].to_print = "Single Refresh";
	data->all_button[0].val = data->flag.asked;
	data->all_button[0].i = 0;
}
