/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:05:03 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/14 23:14:58 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void	stay_in_case(t_data *data)
{
	data->obj.index[0] >= data->obj.nb_camera
	? data->obj.index[0] = 0 : 0;
	data->obj.index[0] < 0 ? data->obj.index[0] =
	data->obj.nb_camera - 1 : 0;
	data->obj.index[1] >= data->obj.nb_item
	? data->obj.index[1] = 0 : 0;
	data->obj.index[1] < 0 ? data->obj.index[1] =
	data->obj.nb_item - 1 : 0;
	if (((t_base *)data->obj.item[data->obj.index[1]]) == NULL)
		data->obj.index[1] = 0;
	data->obj.index[2] >= data->obj.nb_light
	? data->obj.index[2] = 0 : 0;
	data->obj.index[2] < 0 ? data->obj.index[2] =
	data->obj.nb_light - 1 : 0;
	data->obj.type_index > 2 ? data->obj.type_index = 0 : 0;
	data->obj.type_index < 0 ? data->obj.type_index = 2 : 0;
}

static void	input_obj2(t_data *data, char enter)
{
	if (key_check(*data, SDL_SCANCODE_KP_PLUS) && enter == 1)
		data->obj.index[data->obj.type_index] += 1;
	if (key_check(*data, SDL_SCANCODE_KP_MINUS) && enter == 1)
		data->obj.index[data->obj.type_index] -= 1;
	if (key_check(*data, SDL_SCANCODE_KP_PLUS) && enter != 1)
		data->obj.type_index += 1;
	if (key_check(*data, SDL_SCANCODE_KP_MINUS) && enter != 1)
		data->obj.type_index -= 1;
	if (key_check(*data, SDL_SCANCODE_KP_MULTIPLY))
		data->bounce = 0;
	if (key_check(*data, SDL_SCANCODE_KP_PERIOD) && enter == 1)
	{
		data->flag.tree = 1;
		data->bounce += data->bounce < 8 ? 1 : 0;
	}
	else if (key_check(*data, SDL_SCANCODE_KP_PERIOD) && enter != 1)
	{
		data->flag.tree = 1;
		data->bounce > 0 ? data->bounce -= 1 : 0;
	}
	else
		data->flag.tree = 0;
}

static void	input_obj(t_data *data)
{
	void		*tmp;
	void		**obj;
	static char	enter = 1;

	if (key_check(*data, SDL_SCANCODE_KP_ENTER))
		enter *= -1;
	input_obj2(data, enter);
	stay_in_case(data);
	if (data->obj.type_index == 1)
		tmp = (data->obj.item[data->obj.index[1]]);
	else if (data->obj.type_index == 2)
		tmp = &(data->obj.light[data->obj.index[data->obj.type_index]]);
	else
		tmp = &(data->obj.camera[data->obj.index[data->obj.type_index]]);
	obj = &(tmp);
	// if (enter == 1)
	// 	ft_putstr("Current Mode Object\n\n");
	// else
	// 	ft_putstr("Current Mode Index\n\n");
	data->move[data->obj.type_index](data, obj);
}

void		get_input(t_data *data)
{
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	data->input.oldbutton = data->input.button;
	data->input.button = (int)SDL_GetMouseState(&data->input.x, &data->input.y);
	ft_memcpy(data->input.oldkey, data->input.rkey, 250);
	//SDL_PollEvent(&data->input.ev);
	ft_memcpy(data->input.rkey, data->input.key, 250);
}

void		input(t_data *data)
{
	static Uint32	color = 0;
	static char		tmp = 0;
	static void		*tmp2 = NULL;
	int				i;

	i = -1;
	while (++i < 4)
	{

		if (!tmp)
			color = ((t_base *)((t_thread *)data->thread)[i].obj.item[data->obj.index[1]])->effect.color;
		tmp = 1;
		tmp2 = ((t_base *)data->obj.item[data->obj.index[1]]);
		// ((t_base *)((t_thread *)data->thread)[i].obj.item[data->obj.index[1]])->effect.color = color;
		// if (!data->hud.color_obj)
		// {
		// 	printf("crece\n");
		// 	data->screen.preview.sphere.effect.color = ((t_thread *)data->thread)[i].color_pick;
		// }
		// else
		// 	data->screen.preview.sphere.effect.color = ((t_base *)((t_thread *)data->thread)[i].obj.item[data->obj.index[1]])->effect.color;
	}
	// ((t_base *)data->obj.item[data->obj.index[1]])->effect.color = color;
	get_input(data);
	if (data->screen.interface == RUN)
	{
		if (key_check(*data, SDL_SCANCODE_PRINTSCREEN))
			ask_screenshot(data);
		if (key_check(*data, SDL_SCANCODE_V))
			data->flag.pixel =
			(data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
		if (key_check(*data, SDL_SCANCODE_R))
			data->flag.refresh = (data->flag.refresh ? 0 : 1);
		input_obj(data);
		if (key_check(*data, SDL_SCANCODE_L))
		{
			data->flag.video = data->flag.nb_video;
			data->flag.save = 1;
		}
		if (key_check(*data, SDL_SCANCODE_K))
			data->flag.show = (data->flag.show == 1 ? 0 : 1);
		if (data->flag.video)
			framed(data);
		if (data->flag.show && !data->flag.asked)
			show_framed(data);
		light_cursor(data);
		input_filter(data);
		input_hud(data);
		if (key_check(*data, SDL_SCANCODE_O))
			data->flag.antialiasing =
			(data->flag.antialiasing < 3 ? data->flag.antialiasing + 1 : 0);
	}
	i = -1;
	while (++i < 4)
	{
		if (tmp2 != ((t_base *)data->obj.item[data->obj.index[1]]))
			((t_base *)tmp2)->effect.color = color;
		color = ((t_base *)((t_thread *)data->thread)[i].obj.item[data->obj.index[1]])->effect.color;
		if (data->hud.color_obj)
			((t_base *)((t_thread *)data->thread)[i].obj.item[data->obj.index[1]])->effect.color = 0xFFFFFF;
		printf("%d \\ %d\n", data->hud.color_obj, data->hud.last_color_obj);
		if (!data->hud.color_obj && data->hud.last_color_obj)
		{
			((t_base *)((t_thread *)data->thread)[i].obj.item[data->obj.index[1]])->effect.color = ((t_thread *)data->thread)[i].color_pick;
			color = data->screen.preview.sphere.effect.color;
		}
	}
	if (!data->hud.color_obj && data->hud.last_color_obj)
		((t_base *)data->obj.item[data->obj.index[1]])->effect.color = ((t_thread *)data->thread)[i].color_pick;
	data->hud.last_color_obj = data->hud.color_obj;
}
