/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_aa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:29:05 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/22 23:55:13 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_aa(t_data *data, int val)
{
	if (data->flag.antialiasing == val)
		data->flag.antialiasing = 0;
	else
		data->flag.antialiasing = val;
}

void	button_aa(t_data *data)
{
	data->all_button[1].pf = &boo_value_aa;
	data->all_button[1].to_print = "AA";
	data->all_button[1].val = data->flag.antialiasing;
	data->all_button[1].i = 3;
}
