/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 00:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/07 00:05:49 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			create_menu_texture(t_data *data)
{
	data->menu.background = SDL_CreateTexture(data->window.rend,
	SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, 300, data->window.y);
	// Move to Interface ?
}
