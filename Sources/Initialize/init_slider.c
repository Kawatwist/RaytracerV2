/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slider.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:52:46 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/25 17:03:58 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_slider_preview_0(t_data *data)
{
	data->screen.preview.slider[0].init = 1;
	data->screen.preview.slider[0].colorbg = 0x7c7c7c;
	data->screen.preview.slider[0].colorcursor = 0x000000;
	data->screen.preview.slider[0].position.x = 10;
	data->screen.preview.slider[0].position.y = data->window.y - 20;
	data->screen.preview.slider[0].position.w = 280;
	data->screen.preview.slider[0].position.h = 15;
	data->screen.preview.slider[0].cursor.x = 140;
	data->screen.preview.slider[0].cursor.y = data->window.y - 20;
	data->screen.preview.slider[0].cursor.w = 20;
	data->screen.preview.slider[0].cursor.h = 15;
}

void	init_slider_preview_1(t_data *data)
{
	data->screen.preview.slider[1].init = 1;
	data->screen.preview.slider[1].dir = 1;
	data->screen.preview.slider[1].colorbg = 0x909090;
	data->screen.preview.slider[1].colorcursor = 0x000000;
	data->screen.preview.slider[1].position.x = 285;
	data->screen.preview.slider[1].position.y = 85;
	data->screen.preview.slider[1].position.w = 10;
	data->screen.preview.slider[1].position.h = data->window.y * 0.55 - 92;
	data->screen.preview.slider[1].cursor.x = 285;
	data->screen.preview.slider[1].cursor.y = 85;
	data->screen.preview.slider[1].cursor.w = 10;
	data->screen.preview.slider[1].cursor.h = 40;
}

void	init_slider_preview_2(t_data *data)
{
	//FILTER
	data->screen.preview.slider[2].init = 1;
	data->screen.preview.slider[2].colorbg = 0x7c7c7c;
	data->screen.preview.slider[2].colorcursor = 0x000000;
	data->screen.preview.slider[2].position.x = 125;
	data->screen.preview.slider[2].position.y = 25;
	data->screen.preview.slider[2].position.w = 150;
	data->screen.preview.slider[2].position.h = 15;
	data->screen.preview.slider[2].cursor.y = 25;
	data->screen.preview.slider[2].cursor.w = 20;
	data->screen.preview.slider[2].cursor.h = 15;
	data->screen.preview.slider[2].cursor.x = 125 + data->flag.filter * data->screen.preview.slider[2].cursor.w;
	// PATCHER ICI POUR PAS QUE CA SORTE DU TABLEAU
}

void	init_slider_preview_3(t_data *data)
{
	data->screen.preview.slider[3].init = 1;
	data->screen.preview.slider[3].colorbg = 0x7c7c7c;
	data->screen.preview.slider[3].colorcursor = 0x000000;
	data->screen.preview.slider[3].position.x = 125;
	data->screen.preview.slider[3].position.y = 25;
	data->screen.preview.slider[3].position.w = 150;
	data->screen.preview.slider[3].position.h = 15;
	data->screen.preview.slider[3].cursor.x = 125;
	data->screen.preview.slider[3].cursor.y = 25;
	data->screen.preview.slider[3].cursor.w = 20;
	data->screen.preview.slider[3].cursor.h = 15;
	data->screen.preview.slider[3].cursor.x = 125 + data->bounce * 6.5;
}

void	init_slider_preview(t_data *data)
{
	init_slider_preview_0(data);
	init_slider_preview_1(data);
	init_slider_preview_2(data);
	init_slider_preview_3(data);
}
