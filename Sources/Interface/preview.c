/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/21 20:19:59 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			init_preview(t_data *data)
{
	data->screen.preview.cam.origin = fill_vec(0, 0, 0);
	data->screen.preview.cam.direction = normalize(fill_vec(0, 0, 1));
	data->screen.preview.sphere.origin.origin = fill_vec(0, 0, 300);
	data->screen.preview.sphere.rayon = 150.0;
	data->screen.preview.sphere.effect.color = 0xFF0000;
	return (0);
}

void		new_rt(t_data *data)
{
	t_vec	ray;
	static float	val = 200.0;
	static SDL_Rect	petit = {.x = 0, .y = 300, .w = 300, .h=300};

	petit.y = data->window.y - 300;
	SDL_RenderClear(data->window.rend);
	SDL_LockTexture(data->window.txt, NULL, &data->window.pxl, &data->window.pitch);
	/*RT*/

	data->screen.preview.sphere.rayon = val;
	ray.origin = fill_vec(0, 0, 0);
	ray.origin.y = -(data->window.y / 2.0);
	ray.direction = fill_vec(0, 0, 1);
	while (ray.origin.y < data->window.y / 2.0)
	{
		ray.origin.x = -(data->window.x / 2.0);
		while (ray.origin.x < data->window.x / 2.0)
		{
			if ((sphere(&data->screen.preview.sphere, ray)) == -1)
			{
				((int *)data->window.pxl)[(500 + (int)ray.origin.x) + ((500 +(int)ray.origin.y) * data->window.x)] = 0;
			}
			else
				((int *)data->window.pxl)[(500 + (int)ray.origin.x) + ((500 +(int)ray.origin.y) * data->window.x)] = 0xFF00FF;
				//pixel a colorer de la couleur noir
			ray.origin.x += 1.0;
		}
		ray.origin.y += 1.0;
	}
	SDL_UnlockTexture(data->window.txt);
	SDL_RenderCopy(data->window.rend, data->window.txt, NULL, &petit);
	SDL_RenderPresent(data->window.rend);
	SDL_Delay(64);
}
