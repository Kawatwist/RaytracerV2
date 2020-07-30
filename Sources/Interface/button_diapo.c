/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_diapo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:31:41 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/30 14:44:26 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_diapo(t_data *data, int val)
{
	if (data->flag.diapo == val)
		data->flag.diapo = 0;
	else
		data->flag.diapo = val;
}

void	button_diapo(t_data *data)
{
	data->all_button[7].pf = &boo_value_diapo;
	data->all_button[7].to_print = "Diapo";
	data->all_button[7].val = data->flag.diapo;
	data->all_button[7].i = 1;
}

void	boo_value_alpha(t_data *data, int val)
{
	if (data->flag.alpha == val)
		data->flag.alpha = 0;
	else
		data->flag.alpha = val;
}

void	button_alpha(t_data *data)
{
	data->all_button[10].pf = &boo_value_alpha;
	data->all_button[10].to_print = "Alpha";
	data->all_button[10].val = data->flag.alpha;
	data->all_button[10].i = 1;
}

