/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 03:41:10 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/07 22:39:39 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	input_hud(t_data *data)
{
	if (key_check(*data, SDL_SCANCODE_H))
		data->hud.flag_icon = !data->hud.flag_icon;
	if (key_check(*data, SDL_SCANCODE_C))
		data->hud.color_obj = !data->hud.color_obj;
}
