/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:39:29 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/22 23:54:58 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	button_spawn(t_data *data)
{
	data->all_button[10].pf = &boo_value;
	data->all_button[10].to_print = "Spawn";
	data->all_button[10].val = data->flag.diapo;
	data->all_button[10].i = 1;
}
