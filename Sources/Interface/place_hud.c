/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:56:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/19 18:02:57 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		pics_on_screen(t_data *data)
{
	set_hud(data);
	if (data->obj.type_index == 0)
		SDL_RenderCopy(data->window.rend, data->hud.texture[0],
			NULL, &(data->hud.pos[0]));
	if (data->obj.type_index == 1)
		SDL_RenderCopy(data->window.rend, data->hud.texture[data->hud.type_obj],
			NULL, &(data->hud.pos[data->hud.type_obj]));
	if (data->obj.type_index == 2)
		SDL_RenderCopy(data->window.rend, data->hud.texture[2],
			NULL, &(data->hud.pos[2]));
	SDL_RenderCopy(data->window.rend, data->hud.rgb[2],
		NULL, &data->hud.pos[11]);
	SDL_RenderCopy(data->window.rend, data->hud.rgb[1],
		NULL, &data->hud.pos[10]);
	SDL_RenderCopy(data->window.rend, data->hud.rgb[0],
		NULL, &data->hud.pos[9]);
	SDL_RenderCopy(data->window.rend, data->hud.texture[8],
		NULL, &(data->hud.pos[8]));
	return (0);
}
