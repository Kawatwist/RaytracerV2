/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:25:01 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/22 23:55:02 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_show(t_data *data, int val)
{
	if (data->flag.show == val)
		data->flag.show = 0;
	else
		data->flag.show = val;
}

void	button_show(t_data *data)
{
	data->all_button[4].pf = &boo_value_show;
	data->all_button[4].to_print = "Show";
	data->all_button[4].val = data->flag.show;
	data->all_button[4].i = 1;
}
