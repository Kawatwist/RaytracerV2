/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:56:33 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/19 19:20:49 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		set_hud(t_data *data)
{
	set_section(data);
	data->hud.pos[8].x = 0;
	data->hud.pos[8].y = 0;
	data->hud.pos[8].w = data->window.x;
	data->hud.pos[8].h = data->window.y;
}
