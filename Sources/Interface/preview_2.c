/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/29 13:56:07 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				init_preview(t_data *data)
{
	data->screen.preview.light.origin = fill_vec(120, -120, 235);
	data->screen.preview.light.color = 0xFFFFFF;
	data->screen.preview.cam.origin = fill_vec(0, 0, 0);
	data->screen.preview.cam.direction = normalize(fill_vec(0, 0, 1));
	data->screen.preview.sphere.origin.origin = fill_vec(0, 0, 300);
	data->screen.preview.sphere.rayon = 70.0;
	data->screen.preview.sphere.effect.color = 0xFF00FF;
	if (!(data->screen.preview.texture = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, 300, 300)))
		return (1);
	return (0);
}

float			stay_in_case(float value, float min, float max)
{
	if (value > min && value < max)
		return (value);
	return (value < min ? min : max);
}

float			slider(t_data *data, t_slider *slider)
{
	if (mouse_check(data, SDL_BUTTON_LEFT)
		&& (hitbox(data->input.x, data->input.y, &slider->position)))
		slider->selected = 1;
	if (!(data->input.button & SDL_BUTTON_LEFT))
		slider->selected = 0;
	if (slider->selected == 1)
	{
		if (!slider->dir)
			slider->cursor.x = stay_in_case(data->input.x -
			(slider->cursor.w / 2.0), slider->position.x, slider->position.x +
			slider->position.w - slider->cursor.w);
		else
			slider->cursor.y = stay_in_case(data->input.y -
			(slider->cursor.h / 2.0), slider->position.y, slider->position.y +
			slider->position.h - slider->cursor.h);
	}
	draw_rect(data, slider->position, slider->colorbg);
	if (slider->cursor.x <= slider->position.x + slider->position.w)
		draw_rect(data, slider->cursor, slider->colorcursor);
	if (!slider->dir)
		return ((float)(slider->cursor.x - slider->position.x)
			/ (slider->position.w) * 1.07692357396);
		return ((float)(slider->cursor.y - slider->position.y)
		/ (slider->position.h) * 1.0952380);
}
