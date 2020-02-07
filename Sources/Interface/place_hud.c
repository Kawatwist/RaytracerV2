/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:56:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/07 01:25:19 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		pics_on_screen(t_data *data)
{
	int i;

	set_hud(data);
	i = -1;
	while (++i < 4)
	{
		SDL_RenderCopy(data->window.rend, data->hud.texture[i], NULL, &(data->hud.pos[i]));
	}
	return (0);
}
