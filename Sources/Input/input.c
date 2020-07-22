/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:05:03 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/22 20:27:39 by lomasse          ###   ########.fr       */
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
	if (key_check(*data, SDL_SCANCODE_KP_PLUS) && data->obj.type_index != 2)
		data->hud.color_obj = 1;
	if (key_check(*data, SDL_SCANCODE_KP_PERIOD) && enter == 1)
		data->bounce += 1;
	else if (key_check(*data, SDL_SCANCODE_KP_PERIOD) && enter != 1)
		data->bounce > 0 ? data->bounce -= 1 : 0;
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
	data->move[data->obj.type_index](data, obj);
}

void		get_input(t_data *data)
{
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	data->input.oldbutton = data->input.button;
	data->input.button = (int)SDL_GetMouseState(&data->input.x, &data->input.y);
	ft_memcpy(data->input.oldkey, data->input.rkey, 250);
	ft_memcpy(data->input.rkey, data->input.key, 250);
}

static void	set_color_selected(t_data *data)
{
	data->hud.select.color_save = ((t_base *)data->obj.item[data->obj.index[1]])->effect.color;
	if (data->hud.color_obj && data->obj.type_index == 1)
		((t_base *)data->obj.item[data->obj.index[1]])->effect.color = 0xFFFFFF;
	if (data->hud.color_obj && data->obj.type_index == 1)
		data->screen.preview.sphere.effect.color = data->hud.select.color_save;
	if (data->hud.select.color_pick)
		data->hud.select.color_save = data->hud.select.color_pick_save;
}

static void	color_selected(t_data *data)
{
	int		i;

	if (!data->hud.select.selector)
		data->hud.select.selector = 1;
	else
	{
		if (data->hud.select.color_pick && data->hud.color_obj)
			data->hud.select.color_save = data->hud.select.color_pick_save;
		((t_base *)data->obj.item[data->obj.index[1]])->effect.color = data->hud.select.color_save;
		i = -1;
		while (++i < 4)
			((t_base *)((t_thread *)data->thread)[i].obj.item[data->obj.index[1]])->effect.color = data->hud.select.color_save;
	}
	data->hud.select.index_last = data->obj.index[1];
	data->hud.select.color_pick = 0;
}

void		input(t_data *data)
{
	color_selected(data);
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
		if (key_check(*data, SDL_SCANCODE_M))
			data->flag.cam_move = (data->flag.cam_move == 1 ? 0 : 1);
		if (data->flag.video)
			framed(data);
		if (data->flag.show && !data->flag.asked)
			show_framed(data);
		light_cursor(data);
		input_filter(data);
		input_hud(data);
		if (key_check(*data, SDL_SCANCODE_O) && !key_check(*data, SDL_SCANCODE_LCTRL))
			data->flag.antialiasing =
			(data->flag.antialiasing < 3 ? data->flag.antialiasing + 1 : 0);
		else if (key_check(*data, SDL_SCANCODE_O))
			data->flag.antialiasing = 0;
	}
	set_color_selected(data);
}
