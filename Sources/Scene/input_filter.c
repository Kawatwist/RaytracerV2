/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 23:03:52 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/07 23:04:13 by luwargni         ###   ########.fr       */
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
}
