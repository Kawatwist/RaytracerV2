/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_shadow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:39:29 by anboilea          #+#    #+#             */
/*   Updated: 2020/08/01 14:31:33 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_shadow(t_data *data, int val)
{
	if (data->flag.shadow == val)
		data->flag.shadow = 0;
	else
		data->flag.shadow = val;
}

void	button_shadow(t_data *data)
{
	data->all_button[9].pf = &boo_value_shadow;
	data->all_button[9].to_print = "No Shadow";
	data->all_button[9].val = data->flag.shadow;
	data->all_button[9].i = 1;
}

void	boo_value_ambiant(t_data *data, int val)
{
	if (data->flag.ambiant == val)
		data->flag.ambiant = 0;
	else
		data->flag.ambiant = val;
}

void	button_ambiant(t_data *data)
{
	data->all_button[11].pf = &boo_value_ambiant;
	data->all_button[11].to_print = "Ambiant";
	data->all_button[11].val = data->flag.ambiant;
	data->all_button[11].i = 1;
}