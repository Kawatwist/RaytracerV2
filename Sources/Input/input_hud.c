/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 03:41:10 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/20 20:37:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	input_hud(t_data *data)
{
	if (key_check(*data, SDL_SCANCODE_H))
	{
		data->hud.flag_hud = (data->hud.flag_hud ? 0 : 1);
		data->flag.show = 0;
	}
	if (key_check(*data, SDL_SCANCODE_C))
		data->hud.color_obj = !data->hud.color_obj;
}
