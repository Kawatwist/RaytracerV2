/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:48:39 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/24 20:01:26 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		hitbox(int	x, int	y, SDL_Rect *pos)//surement mettre autre part
{
	if (x >= pos->x && y >= pos->y && x <= pos->x + pos->w && y <= pos->y + pos->h)
		return (1);
	return (0);
}

static void		mouse_get_info(t_data *data, SDL_Rect *pos)
{
	pos->x = (data->window.x / 500.0) * 280;
	pos->y = (data->window.y / 500.0) * 233;
	pos->w = (data->window.x / 500.0) * 189;
	pos->h = (data->window.x / 500.0) * 164;
	if ((hitbox(data->input.x, data->input.y, pos)) == 1)
		data->screen.interface = INFO;
}

static void		mouse_get_run(t_data *data, SDL_Rect *pos)
{
	pos->x = (data->window.x / 500.0) * 35.0;
	pos->y = (data->window.y / 500.0) * 255.0;;
	pos->w = (data->window.x / 500.0) * 170;
	pos->h = (data->window.y / 500.0) * 142;
	if ((hitbox(data->input.x, data->input.y, pos)) == 1)
		data->screen.interface = RUN;
}

int				info_screen(t_data *data)
{
	if (key_check(*data, SDL_SCANCODE_BACKSPACE))
		data->screen.interface = HOME;
	SDL_RenderCopy(data->window.rend, data->screen.scenetxt[3], NULL, NULL);
	SDL_RenderPresent(data->window.rend);
	return (0);
}

int				 home_screen(t_data *data)
{
	SDL_Rect	pos;

	printf("%d || %d\n", data->input.x, data->input.y);
	if (data->flag.refresh == 0)
		data->flag.asked = 1;
	get_input(data);
	if ((data->input.button = (int)SDL_GetMouseState(&data->input.x, &data->input.y)) == 1)
	{
		mouse_get_run(data, &pos);
		mouse_get_info(data, &pos);
	}
	if (key_check(*data, SDL_SCANCODE_RETURN))
		data->screen.interface = RUN;
	SDL_RenderCopy(data->window.rend, data->screen.scenetxt[0], NULL, NULL);
	SDL_RenderPresent(data->window.rend);
	return (0);
}
