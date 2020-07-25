/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_advance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:39:29 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/25 16:54:31 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_advance(t_data *data, int val)
{
	if (data->flag.adv == val)
		data->flag.adv = 0;
	else
		data->flag.adv = val;
}

void	button_advance(t_data *data)
{
	data->all_button[8].pf = &boo_value_advance;
	data->all_button[8].to_print = "Advance";
	data->all_button[8].val = data->flag.adv;
	data->all_button[8].i = 1;
}
