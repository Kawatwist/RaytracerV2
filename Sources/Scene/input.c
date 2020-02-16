/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:05:03 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/15 16:38:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

static void	get_input(t_data *data)
{
	printf("Input [1]\n");
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	printf("Input [2]\n");
	data->input.button = (int)SDL_GetMouseState(&data->input.x, &data->input.y);
	ft_memcpy(data->input.oldkey, data->input.rkey, 250);
	printf("Input [3]\n");
	// SDL_PollEvent(&data->input.ev);
	ft_memcpy(data->input.rkey, data->input.key, 250);
}

void		input(t_data *data)
{
	static t_c33	adad = {.color = 0, .flag = 1};

	printf("Input [1]\n");
	get_input(data);
	printf("Input [2]\n");
	if (key_check(*data, SDL_SCANCODE_PRINTSCREEN))
		create_screenshot(data, data->window.pxl);
	printf("Input [3]\n");
	if (key_check(*data, SDL_SCANCODE_V))
		data->flag.pixel = (data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
	printf("Input [4]\n");
	if (key_check(*data, SDL_SCANCODE_R))
		data->flag.refresh = (data->flag.refresh ? 0 : 1);
	printf("Input [5]\n");
	if (adad.flag == 0 && data->hud.color_obj)
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color =
		adad.color;
	printf("Input [6]\n");
	// light_cursor(data);
	input_obj(data);
	printf("Input [7]\n");
	input_filter(data);
	printf("Input [8]\n");
	input_hud(data);
	printf("Input [9]\n");
	if (data->hud.color_obj)
	{
		adad.color =
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color;
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color =
		0xFFFFFF;
		adad.flag = 0;
	}
	printf("Input [10]\n");
	if (key_check(*data, SDL_SCANCODE_O))
		data->flag.antialiasing = (data->flag.antialiasing < 3 ? data->flag.antialiasing + 1 : 0);
}
