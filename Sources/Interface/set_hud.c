/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:56:33 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/01 03:54:36 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include "rt.h"

void		set_hud(t_data *data)
{
	data->hud.ifquow[0].x = 0;
	data->hud.ifquow[0].y = 0;
	data->hud.ifquow[0].w = 60;
	data->hud.ifquow[0].h = 60;
	data->hud.ifquow[1].x = 60;
	data->hud.ifquow[1].y = 60;
	data->hud.ifquow[1].w = 60;
	data->hud.ifquow[1].h = 60;
	data->hud.ifquow[2].x = 120;
	data->hud.ifquow[2].y = 120;
	data->hud.ifquow[2].w = 60;
	data->hud.ifquow[2].h = 60;
}
