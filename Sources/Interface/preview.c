/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/10 00:14:23 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			init_preview(t_data *data)
{
	data->screen.preview.light.origin = fill_vec(120, -120, 235);
	data->screen.preview.light.color = 0xFFFFFF;
	data->screen.preview.cam.origin = fill_vec(0, 0, 0);
	data->screen.preview.cam.direction = normalize(fill_vec(0, 0, 1));
	data->screen.preview.sphere.origin.origin = fill_vec(0, 0, 300);
	data->screen.preview.sphere.rayon = 100.0;
	data->screen.preview.sphere.effect.color = 0xFF00FF;
	if (!(data->screen.preview.texture = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, 300, 300)))
		return (1); // Protection
	return (0);
}

float	stay_in_case(float value, float min, float max)
{
	if (value > min && value < max)
		return (value);
	return (value < min ? min : max);
}

float			slider(t_data *data, t_slider *slider)
{
	if ((data->input.button & SDL_BUTTON_LEFT) &&
		(hitbox(data->input.x, data->input.y, &slider->position)) == 1)
		slider->selected = 1;
	if (!(data->input.button & SDL_BUTTON_LEFT))
		slider->selected = 0;
	if (slider->selected == 1)
	{
		if (!slider->dir)
			slider->cursor.x =
			stay_in_case(data->input.x - (slider->cursor.w / 2.0),
			slider->position.x, slider->position.x + slider->position.w);
		else
			slider->cursor.y =
			stay_in_case(data->input.y - (slider->cursor.h / 2.0),
			slider->position.y, slider->position.y + slider->position.h);
	}
	draw_rect(data, slider->position, slider->colorbg);
	draw_rect(data, slider->cursor, slider->colorcursor);
	if (!slider->dir)
		return ((float)(slider->cursor.x - slider->position.x)
			/ (slider->position.w));
		return ((float)(slider->cursor.y - slider->position.y)
		/ (slider->position.h));
}

static	void	init_slider_preview(t_data *data)
{
	data->screen.preview.slider[0].init = 1;
	data->screen.preview.slider[0].colorbg = 0x7c7c7c;
	data->screen.preview.slider[0].colorcursor = 0x000000;
	data->screen.preview.slider[0].position.x = 10;
	data->screen.preview.slider[0].position.y = data->window.y - 80;
	data->screen.preview.slider[0].position.w = 280;
	data->screen.preview.slider[0].position.h = 15;
	data->screen.preview.slider[0].cursor.x = 140;
	data->screen.preview.slider[0].cursor.y = data->window.y - 80;
	data->screen.preview.slider[0].cursor.w = 20;
	data->screen.preview.slider[0].cursor.h = 15;
	data->screen.preview.slider[1].init = 1;
	data->screen.preview.slider[1].dir = 1;
	data->screen.preview.slider[1].colorbg = 0x909090;
	data->screen.preview.slider[1].colorcursor = 0x000000;
	data->screen.preview.slider[1].position.x = 285;
	data->screen.preview.slider[1].position.y = 85;
	data->screen.preview.slider[1].position.w = 10;
	data->screen.preview.slider[1].position.h = data->window.y - 540;
	data->screen.preview.slider[1].cursor.x = 285;
	data->screen.preview.slider[1].cursor.y = 300;
	data->screen.preview.slider[1].cursor.w = 10;
	data->screen.preview.slider[1].cursor.h = 40;
}

static float	moving_light(t_data *data)
{
	static float		var = 0;
	static char			flag = 0;

	var += 5;
	if (var > 350)
		var = 5;
	if (!flag)
		data->screen.preview.light.origin.x -= 2;
	else
		data->screen.preview.light.origin.x += 2;
	if (data->screen.preview.light.origin.x < -120)
		flag = 1;
	if (data->screen.preview.light.origin.x > 120)
		flag = 0;
	return (var);
}

static void	text_info(t_data *data)
{
	// static char *str = NULL;

	if (data->flag.video)
	{
		data->font.str = ft_strdup("Rendu Video En cours\0");
		print_text(data, 300, data->window.y - 40, 30);
		// Draw Text
	}
	if (data->bounce)
	{
		data->font.str = ft_strjoinfree("Bounce :\0", ft_itoa(data->bounce), 2);
		print_text(data, 300, data->window.y - 80, 30);
	}
	// str = input_hud_text(data, str);
	// data->font.str = ft_strdup(str);
	// print_text(data, 300, data->window.y - 40, 30);
}

void		new_rt(t_data *data)
{
	static	SDL_Rect	petit = {.x = 0, .y = 200, .w = 200, .h = 200};

	petit.y = data->window.y - 300;
	if (!data->screen.preview.slider[0].init)
		init_slider_preview(data);
	if (!data->hud.color_obj)
		data->screen.preview.sphere.effect.color =
			switchcolor((int)moving_light(data));
	SDL_LockTexture(data->screen.preview.texture, NULL,
		&data->screen.preview.pxl, &data->window.pitch);
	find_slider_pos(data->screen.preview.sphere.effect.color);
	data->screen.preview.slider[0].value =
		slider(data, &data->screen.preview.slider[0]);
	mini_rt(data);
	color_picker(data);
	draw_circle(setup_circle(color_to_pos(145, 145,
		data->screen.preview.sphere.effect.color), 0x333333,
		(0x1000000007), data->screen.preview.pxl));
	SDL_UnlockTexture(data->screen.preview.texture);
	data->screen.preview.slider[1].value =
		slider(data, &data->screen.preview.slider[1]);
	text_info(data);
}
