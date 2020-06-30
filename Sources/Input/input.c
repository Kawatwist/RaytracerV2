/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:05:03 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/29 19:51:34 by lomasse          ###   ########.fr       */
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
	if (enter == 1)
		ft_putstr("Current Mode Object\n\n");
	else
		ft_putstr("Current Mode Index\n\n");
	data->move[data->obj.type_index](data, obj);
}

void	get_input(t_data *data)
{
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	data->input.button = (int)SDL_GetMouseState(&data->input.x, &data->input.y);
	ft_memcpy(data->input.oldkey, data->input.rkey, 250);
	// SDL_PollEvent(&data->input.ev);
	ft_memcpy(data->input.rkey, data->input.key, 250);
}
// REMOVE
void		check_mutex(t_data *data)
{
	int i = -1;
	if (key_check(*data, SDL_SCANCODE_G))
	{
		while (++i < 4)
		{
			while (pthread_mutex_trylock(&((t_thread *)(data)->thread)[i].mutex))
				;
			((t_thread *)(data)->thread)[i].signal = SIGTSTP;
			pthread_mutex_unlock(&((t_thread *)(data)->thread)[i].mutex);
		}
	}
}

void		ask_screenshot(t_data *data)
{
	const SDL_MessageBoxButtonData buttons[] = {{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "TGA" },
			{ 0, 1, "BMP" },{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" },};
	const SDL_MessageBoxColorScheme colorScheme = {{{255, 0, 0},
			{0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255,   0, 255}}};
	const SDL_MessageBoxData messageboxdata = {SDL_MESSAGEBOX_INFORMATION, NULL, "Screenshot", "Select a format :", SDL_arraysize(buttons), buttons, &colorScheme};
	int buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
	{
		SDL_Log("error displaying message box");
	}
	if (buttonid == 0)
		create_screenshot(data, data->window.pxl);
	else if (buttonid == 1)
		create_screenshot_bmp(data, data->window.pxl, (char **)(&(("./Screenshot/screenshot_0\0"))), 1);
}

void		input(t_data *data)
{
	static t_c33	adad = {.color = 0, .flag = 1};
	void			*tmp;

	tmp = data->obj.item[data->obj.index[1]];
	get_input(data);//segfault ici
	if (data->screen.interface == RUN)
	{
		if (key_check(*data, SDL_SCANCODE_PRINTSCREEN))
			ask_screenshot(data);
		if (key_check(*data, SDL_SCANCODE_V))
			data->flag.pixel = (data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
		if (key_check(*data, SDL_SCANCODE_R))
			data->flag.refresh = (data->flag.refresh ? 0 : 1);
		if (adad.flag == 0 && data->hud.color_obj)
			((t_base *)(tmp))->effect.color = adad.color;
		if (key_check(*data, SDL_SCANCODE_L))
		{
			data->flag.video = data->flag.nb_video;
			data->flag.save = 1;
		}
		if (key_check(*data, SDL_SCANCODE_K))
			data->flag.show = 1;
		if (data->flag.video)
			framed(data);
		if (data->flag.show && !data->flag.asked)
			show_framed(data);
		light_cursor(data);
		input_obj(data);
		input_filter(data);
		input_hud(data);
		if (data->hud.color_obj)
		{
			adad.color = ((t_base *)(tmp))->effect.color;
			((t_base *)(tmp))->effect.color = 0xFFFFFF;
			adad.flag = 0;
		}
		if (key_check(*data, SDL_SCANCODE_O))
			data->flag.antialiasing = (data->flag.antialiasing < 3 ? data->flag.antialiasing + 1 : 0);
		if (data->flag.video)
		{

		}
	}
}

	// if (key_check(*data, SDL_SCANCODE_PRINTSCREEN))
	// 	create_screenshot(data, data->window.pxl);
	// if (key_check(*data, SDL_SCANCODE_V))
	// 	data->flag.pixel = (data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
	// if (key_check(*data, SDL_SCANCODE_R))
	// 	data->flag.refresh = (data->flag.refresh ? 0 : 1);

	// if (select.flag == 0 && data->hud.color_obj)
	// {
	// 	for (int i = 0; i < 4; i ++)
	// 		((t_base *)(((t_thread *)data->thread)[i].obj.item[data->obj.index[1]]))->effect.color =
	// 			select.color;
	// 	((t_base *)data->obj.item[data->obj.index[1]])->effect.color = select.color;
	// }
	// light_cursor(data);
	// input_obj(data);
	// input_filter(data);
	// input_hud(data);
	// if (data->hud.color_obj)
	// {
	// 	select.color =
	// 	((t_base *)(((t_thread *)data->thread)[0].obj.item[data->obj.index[1]]))->effect.color;
	// 	for (int i = 0; i < 4; i ++)
	// 	((t_base *)(((t_thread *)data->thread)[i].obj.item[data->obj.index[1]]))->effect.color =
	// 		0xF3DA75;
	// 	((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color =
	// 		0xF3DA75;
	// 	select.flag = 0;
	// }

	// if (key_check(*data, SDL_SCANCODE_O))
	// 	data->flag.antialiasing = (data->flag.antialiasing < 3 ? data->flag.antialiasing + 1 : 0);
	// check_mutex(data);
// }
