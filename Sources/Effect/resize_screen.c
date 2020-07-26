/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 18:25:17 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/26 13:39:30 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		resize_size(t_data *data, int check[2])
{
	data->flag.asked = 1;
	if (check[0] < 1000)
		check[0] = 1000;
	if (check[1] < 1000)
		check[1] = 1001;
	if (check[1] % 4)
	{
		SDL_SetWindowSize(data->window.window, check[0], check[1] +
			(4 - (check[1] % 4)));
		check[1] = check[1] + (4 - (check[1] % 4));
	}
	else
		SDL_SetWindowSize(data->window.window, check[0], check[1]);
	SDL_GetWindowSize(data->window.window, (int*)(&data->window.x),
		(int*)(&data->window.y));
}

static void		resize_thread(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		((t_thread *)data->thread)[i].x = data->window.x;
		((t_thread *)data->thread)[i].y = data->window.y;
		ft_memcpy((((t_thread *)data->thread)[i].obj.camera),
			(data->obj.camera), sizeof(t_camera) * data->obj.nb_camera);
		((t_thread *)data->thread)[i].obj.nb_camera = data->obj.nb_camera;
	}
}

void			resize(t_data *data)
{
	static int	x;
	static int	y;
	int			check[2];

	x = data->window.x;
	y = data->window.y;
	SDL_GetWindowSize(data->window.window, &check[0], &check[1]);
	if (x != check[0] || y != check[1])
	{
		resize_size(data, check);
		create_menu_texture(data);
		SDL_DestroyTexture(data->window.txt);
		SDL_DestroyTexture(data->window.oldtxt);
		data->window.txt = SDL_CreateTexture(data->window.rend,
			SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
			data->window.y);
		data->window.oldtxt = SDL_CreateTexture(data->window.rend,
			SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
			data->window.y);
		init_cam(data);
		resize_thread(data);
	}
}
