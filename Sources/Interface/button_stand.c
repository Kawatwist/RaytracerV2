/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_stand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:30:03 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/22 23:54:56 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value(t_data *data, int val)
{
	int value;

	(void)data;
	(void)val;
	value = 0;
	if (value == 1)
		value = 0;
	else
		value = 1;
}

void	button_stand(t_data *data, int i)
{
	data->all_button[i].pf = &boo_value;
	data->all_button[i].i = 0;
	data->all_button[i].val = 0;
	data->all_button[i].to_print = "EMPTY";
	data->all_button[i].type = 0;
}
