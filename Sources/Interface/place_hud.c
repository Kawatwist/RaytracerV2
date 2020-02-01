/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:56:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/01 03:54:02 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		DROP_THE_PICS_ON_THE_SCREEN(t_data *data)
{
	set_hud(data);
	for(int i = 0;i < 3;i++)
	{
		SDL_RenderCopy(data->window.rend, data->hud.iqfow[i], NULL, &(data->hud.ifquow[i]));
	}
	return (0);
}
