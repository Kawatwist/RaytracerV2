/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:56:33 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/08 08:18:29 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
// { > 1.77

void		set_hud(t_data *data)//l'emplacement des icones
{

	/*CAM*/
	if (data->obj.type_index == 0)
	{
		if (data->hud.texture[1])
			SDL_DestroyTexture(data->hud.texture[1]);
		if (data->hud.texture[2])
			SDL_DestroyTexture(data->hud.texture[2]);
		data->hud.pos[0].x = data->window.x / 80.0;
		data->hud.pos[0].y = data->window.y / 1.112;
		data->hud.pos[0].w = (data->window.x / 500.0) * 35.0;
		data->hud.pos[0].h = (data->window.y / 500.0) * 35.0;
	}
	/*OBJ*/
	if (data->obj.type_index == 1)
	{
		if (data->hud.texture[0])
			SDL_DestroyTexture(data->hud.texture[0]);
		if (data->hud.texture[2])
			SDL_DestroyTexture(data->hud.texture[2]);
		data->hud.pos[1].x = data->window.x / 80.0;
		data->hud.pos[1].y = data->window.y / 1.112;
		data->hud.pos[1].w = (data->window.x / 500.0) * 35.0;
		data->hud.pos[1].h = (data->window.y / 500.0) * 35.0;
	}
	/*LIGHT*/
	if (data->obj.type_index == 2)
	{
		if (data->hud.texture[0])
			SDL_DestroyTexture(data->hud.texture[0]);
		if (data->hud.texture[1])
			SDL_DestroyTexture(data->hud.texture[1]);
		data->hud.pos[2].x = data->window.x / 80.0;
		data->hud.pos[2].y = data->window.y / 1.112;
		data->hud.pos[2].w = (data->window.x / 500.0) * 35.0;
		data->hud.pos[2].h = (data->window.y / 500.0) * 35.0;
	}
	/*HUD*/
	data->hud.pos[3].x = 0;
	data->hud.pos[3].y = 0;
	data->hud.pos[3].w = data->window.x;
	data->hud.pos[3].h = data->window.y;
}
	// data->hud.pos[1].x = 8;
	// printf("%d\n", data->hud.pos[1].x);
	// data->hud.pos[1].y = 454;
	// data->hud.pos[1].w = 30;
	// data->hud.pos[1].h = 30;

	// data->hud.pos[1].x = 16;
	// printf("%d\n", data->hud.pos[1].x);
	// data->hud.pos[1].y = 908;
	// data->hud.pos[1].w = 60;
	// data->hud.pos[1].h = 60;
