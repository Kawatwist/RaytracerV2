/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 23:03:52 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/25 16:28:14 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		input_filter(t_data *data)
{
	
	if (key_check(*data, SDL_SCANCODE_1))
		data->flag.filter = (data->flag.filter == 0) ? 1 : 0;
	if (key_check(*data, SDL_SCANCODE_2))
		data->flag.filter = (data->flag.filter == 0) ? 2 : 0;
	if (key_check(*data, SDL_SCANCODE_3))
		data->flag.filter = (data->flag.filter == 0) ? 3 : 0;
	if (key_check(*data, SDL_SCANCODE_4))
		data->flag.filter = (data->flag.filter == 0) ? 4 : 0;
	if (key_check(*data, SDL_SCANCODE_5))
		data->flag.filter = (data->flag.filter < 5 ||
		data->flag.filter > 8) ? 5 : data->flag.filter + 1;
	if (key_check(*data, SDL_SCANCODE_N))
		data->flag.normal = (data->flag.normal == 0 ? 1 : 0);
}
