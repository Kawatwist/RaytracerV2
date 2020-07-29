/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:31:26 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/29 13:50:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	input_textures(t_data *data, void **obj, char ctrl)
{
	if (key_hold(data, SDL_SCANCODE_KP_0) && !ctrl &&
	(*(t_base **)obj)->effect.texture < 255)
		(*(t_base **)obj)->effect.texture += 1;
	else if (key_hold(data, SDL_SCANCODE_KP_0) && ctrl &&
	(*(t_base **)obj)->effect.texture > 0)
		(*(t_base **)obj)->effect.texture -= 1;
	if (key_hold(data, SDL_SCANCODE_1) && !ctrl &&
	(*(t_base **)obj)->effect.normal < 255)
		(*(t_base **)obj)->effect.normal += 1;
	else if (key_hold(data, SDL_SCANCODE_1) && ctrl &&
	(*(t_base **)obj)->effect.normal > 0)
		(*(t_base **)obj)->effect.normal -= 1;
}
