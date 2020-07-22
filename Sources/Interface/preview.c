/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/22 23:15:30 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

static void		text_info(t_data *data)
{
	if (data->flag.video)
	{
		data->font.str = ft_strdup("Rendu Video En cours\0");
		print_text(data, 300, data->window.y - 40, 30);
	}
	if (data->bounce)
	{
		data->font.str = ft_strjoinfree("Bounce :\0", ft_itoa(data->bounce), 2);
		print_text(data, 300, data->window.y - 80, 30);
	}
}

static void		get_color_picker(t_data *data)
{
	double	distance;
	int		radius;
	int		radius_min;

	distance = 0.0;
	radius = 120;
	radius_min = 85;
	distance = sqrt((double)((data->input.x - 30) - radius) *
	((data->input.x - 30) - radius) + ((data->input.y - 650) - radius) *
	((data->input.y - 650) - radius));
	if (data->input.button & SDL_BUTTON_LEFT &&
	distance > radius_min && distance < radius)
	{
		data->hud.select.color_pick = 1;
		data->hud.select.color_pick_save =
		hue(data, find_color_chroma(data->input.x - 30, data->input.y - 650));
	}
}

void			new_rt(t_data *data)
{
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
	data->screen.preview.slider[1].position.h = data->window.y * 0.55 - 92;
	data->screen.preview.slider[1].value =
	slider(data, &data->screen.preview.slider[1]);
	data->screen.preview.slider[0].position.y = data->window.y * 0.55 + 60;
	data->screen.preview.slider[0].cursor.y = data->window.y * 0.55 + 60;
	get_color_picker(data);
	text_info(data);
}
