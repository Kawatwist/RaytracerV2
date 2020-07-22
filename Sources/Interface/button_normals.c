/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_normals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:22:41 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/22 23:55:09 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	boo_value_normals(t_data *data, int val)
{
	if (data->flag.normal == val)
		data->flag.normal = 0;
	else
		data->flag.normal = val;
}

void	button_normals(t_data *data)
{
	data->all_button[2].pf = &boo_value_normals;
	data->all_button[2].to_print = "Normals";
	data->all_button[2].val = data->flag.normal;
	data->all_button[2].i = 1;
}
