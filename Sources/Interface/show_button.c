/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:49:48 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/26 14:39:24 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_nbvideo_bg(t_data *data)
{
	SDL_Rect dst;

	dst.x = 10;
	dst.y = 5;
	dst.w = 200;
	dst.h = 20;
	draw_rect(data, dst, 0xffffff);
	dst.x = 11;
	dst.y = 6;
	dst.w = 198;
	dst.h = 18;
	draw_rect(data, dst, 0x333333);
}

void	video_settings_2(t_data *data, char *str)
{
	if (data->input.key[SDL_SCANCODE_RETURN] &&
	!data->input.oldkey[SDL_SCANCODE_RETURN] && str && data->flag.typing)
	{
		data->flag.typing = 0;
		if (str)
		{
			data->flag.nb_video = ft_atoi(str) > 4095 ? 4095 : ft_atoi(str);
			free(str);
		}
		str = NULL;
	}
}

void	video_settings(t_data *data)
{
	static char *str = NULL;

	if (data->input.x >= 10 && data->input.x <= 210 && data->input.y >= 5
	&& data->input.y <= 25 && data->input.button & SDL_BUTTON_LEFT)
	{
		data->flag.typing = 1;
		if (str)
			free(str);
		str = NULL;
	}
	else if (data->input.button & SDL_BUTTON_LEFT)
		data->flag.typing = 0;
	if (data->flag.typing == 1 && ft_strlen(str) < 4)
		str = input_hud_text(data, str);
	if (str)
	{
		data->font.str = ft_strdup(str);
		print_text(data, 115, 4, 20);
	}
	video_settings_2(data, str);
}

void	show_button(t_data *data)
{
	int			i;
	int			j;
	SDL_Rect	pos;
	int			selector;

	pos.x = 245;
	pos.y = 95;
	selector = 2;
	init_case(data, 1);
	i = (int)(data->screen.preview.slider[1].value * CASE_NBR);
	j = i;
	while (i < CASE_NBR && (i - j) * 45 < data->window.y * 0.5 - 92)
	{
		draw_background_box(data, pos.y);
		if (data->all_button[i].type == 0)
			draw_button(data, pos.x, pos.y, data->all_button[i]);
		else
		{
			draw_slider(data, pos.y, selector);
			selector++;
		}
		i++;
		pos.y += 45;
	}
}

void	show_txt(t_data *data)
{
	static char		*tab[] = {"Camera :", "Object :", "Lights :"};
	int			i;
	int			j;
	SDL_Rect	pos;

	pos.x = 245;
	pos.y = 95;
	i = (int)(data->screen.preview.slider[1].value * CASE_NBR);
	j = i;
	while (i < CASE_NBR && (i - j) * 45 < data->window.y * 0.5 - 92)
	{
		data->font.str = ft_strdup(data->all_button[i].to_print);
		print_text(data, 15, pos.y, 25);
		i++;
		pos.y += 45;
	}
	data->font.str = ft_strdup("Options");
	print_text(data, 100, 40, 25);
	data->font.str = ft_strdup("Color Picker");
	print_text(data, 60, data->window.y * 0.55 + 10, 25);
	
	data->font.str = ft_strdup(tab[data->obj.type_index]);
	print_text(data, 20, data->window.y - 40, 25);
	data->font.str = ft_itoa(data->obj.index[data->obj.type_index]);
	print_text(data, 215, data->window.y - 40, 25);
}
