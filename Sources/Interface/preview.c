/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/05 22:52:54 by lomasse          ###   ########.fr       */
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
	data->screen.preview.texture = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, 300, 300); // Protection
	return (0);
}

int			switchcolor(int h)
{
	int		color;

	if (h > 0 && h < 121)
	{
		color = (h * 255 / 120) << 8;
		color += (255 - ((color & 0xFF00) >> 8));
	}
	else if (h < 241)
	{
		color = ((h - 120) * 255 / 120) << 16;
		color += (255 - ((color & 0xFF0000) >> 16)) << 8;
	}
	else
	{
		color = ((h - 240) * 255) / 120;
		color += (255 - (color & 0xFF)) << 16;
	}
	return (color);
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

static int		find_color_chroma(int i, int j)
{
	int		pos;
	float	dot;

	dot = (dot_product(normalize(sub_vec(fill_vec(i, j, 0), fill_vec(150, 150, 0))), fill_vec(0, -1, 0)) + 1.0) * 90.0;
	pos = (i <= 150 ? 360 - dot: dot);
	pos < 360 ? pos += 360 : 0;
	pos > 360 ? pos -= 360 : 0;
	return (switchcolor(pos));
}

static t_circle	setup_circle(t_point pos, int color, long int	radius, void *pxl)
{
	t_circle circle;

	circle.pxl = pxl;
	circle.x = pos.x;
	circle.y = pos.y;
	circle.color = color;
	circle.r_inside = ((Uint64)radius) & 0xFFFFFFFF;
	circle.r_outside = ((Uint64)radius) >> 32;
	return (circle);
}

static void		draw_circle(t_circle circle)
{
	int		i;
	int		j;
	float	distance;

	i = 0;
	while (i++ <= 2 * circle.r_outside)
	{
		j = 0;
		while (j++ <= 2 * circle.r_outside)
		{
			distance = sqrt((double)(i - circle.r_outside) * (i - circle.r_outside) +
									(j - circle.r_outside) * (j - circle.r_outside));
			if (distance < circle.r_outside && distance > circle.r_inside)
				((int *)circle.pxl)[i + ((j + circle.y) * 300) + circle.x] = circle.color;
		}
	}
}

static	void	color_picker(t_data *data)
{
	double	distance;
	int		radius;
	int		radius_min;
	int		i;
	int		j;

	distance = 0.0;
	radius = 150;
	radius_min = 115;
	i = 0;
	j = 0;
	while (i++ <= 2 * radius)
	{
		j = 0;
		while (j++ <= 2 * radius)
		{
			distance = sqrt((double)(i - radius) * (i - radius) +
									(j - radius) * (j - radius));
			if (distance < radius && distance > radius_min)
				((int *)data->screen.preview.pxl)[i + (j * 300)] = find_color_chroma(i, j);
		}
	}
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
	if (data->flag.video)
	{
		data->font.str = ft_strdup("Rendu En cours\0");
		print_text(data, 300, data->window.y - 40, 30);
		// Draw Text
	}
}
static t_point	color_to_pos(int posx, int posy, int color)
{
	t_point pos;
	float	theta;

	theta = 0;
	if (color & 0xFF0000)
		theta += ((((color & 0xFF0000) >> 16) / 255.0) * 90.0);
	if (color & 0xFF00)
		theta += (((color & 0xFF00) >> 8) / 255.0) * 180.0;
	if (color & 0xFF)
		theta += (((color & 0xFF) >> 0) / 255.0) * 240.0;
	pos.x = posx +  100 * cos(theta);
	pos.y = posy +  100 * sin(theta);
	printf("%#x => %f ||| %f\n", color, pos.x, pos.y);
	return (pos);
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
	mini_rt(data);
	color_picker(data);
	// draw_circle(setup_circle(color_to_pos(150, 150, data->screen.preview.sphere.effect.color), 0x0, (0x150000007), data->screen.preview.pxl));
	SDL_UnlockTexture(data->screen.preview.texture);
	slider(data, &data->screen.preview.slider[0]);
	slider(data, &data->screen.preview.slider[1]);
	text_info(data);
}
