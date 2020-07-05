/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:31:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/05 21:43:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	interface_grey(t_data *data)
{
	void			*pxl;
	int				pitch;
	int				color;
	unsigned int	i;

	if (data->flag.time)
	{
		SDL_LockTexture(data->menu.background, NULL, &pxl, &pitch);
		i = 0;
		while (i < 300 * data->window.y)
		{
			color = (((unsigned char *)pxl)[(i << 2) + 1] +
					((unsigned char *)pxl)[(i << 2) + 2] +
					((unsigned char *)pxl)[(i << 2) + 3]) / 3;
			((unsigned int *)pxl)[i] =
			(0xFF << 24) + (color << 16) + (color << 8) + (color << 0);
			i++;
		}
		SDL_UnlockTexture(data->menu.background);
	}
}
