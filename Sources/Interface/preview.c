/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/28 23:04:37 by luwargni         ###   ########.fr       */
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
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, 300, 300);

	return (0);
}

static int				mix(int i, int j)
{
	unsigned char base[4];
	unsigned char light[4];
	unsigned char ret[4];

	base[0] = (i & 0xFF) >> 0;
	base[1] = (i & 0xFF00) >> 8;
	base[2] = (i & 0xFF0000) >> 16;
	base[3] = (i & 0xFF000000) >> 24;
	light[0] = (j & 0xFF) >> 0;
	light[1] = (j & 0xFF00) >> 8;
	light[2] = (j & 0xFF0000) >> 16;
	light[3] = (j & 0xFF000000) >> 24;
	ret[0] = base[0] + light[0] > 255 ? 255 : base[0] + light[0];
	ret[1] = base[1] + light[1] > 255 ? 255 : base[1] + light[1];
	ret[2] = base[2] + light[2] > 255 ? 255 : base[2] + light[2];
	ret[3] = base[3] + light[3] > 255 ? 255 : base[3] + light[3];
	i = (ret[3] << 24) + (ret[2] << 16) + (ret[1] << 8) + (ret[0] << 0);
	return (i);
}

static int				apply_mult_3(int i, int j, float d)
{
	int fix;

	fix =
	((int)(((int)((int)((i & 0xFF000000) >> 24) * d) << 24) & 0xFF000000) +
		(((int)(((int)((int)((i & 0xFF0000) >> 16) * d) << 16) & 0xFF0000) +
		(((int)(((int)((int)((i & 0xFF00) >> 8) * d) << 8) & 0xFF00) +
		(((int)(((int)((int)((i & 0xFF) >> 0) * d) << 0) & 0xFF))))))));
	fix = mix(j, fix);
	return (fix);
}


static int				apply_mult_2(int i, float d)
{
	return (
	((int)(((int)((int)((i & 0xFF000000) >> 24) * d) << 24) & 0xFF000000) +
	(((int)(((int)((int)((i & 0xFF0000) >> 16) * d) << 16) & 0xFF0000) +
	(((int)(((int)((int)((i & 0xFF00) >> 8) * d) << 8) & 0xFF00) +
	(((int)(((int)((int)((i & 0xFF) >> 0) * d) << 0) & 0xFF)))))))));
}

static int				apply_mult(int i, int j, float d)
{
	unsigned char base[4];
	unsigned char light[4];
	unsigned char ret[4];

(void)d;
	base[0] = (i & 0xFF) >> 0;
	base[1] = (i & 0xFF00) >> 8;
	base[2] = (i & 0xFF0000) >> 16;
	base[3] = (i & 0xFF000000) >> 24;
	light[0] = (j & 0xFF) >> 0;
	light[1] = (j & 0xFF00) >> 8;
	light[2] = (j & 0xFF0000) >> 16;
	light[3] = (j & 0xFF000000) >> 24;
	ret[0] = sqrtf(base[0] * light[0]);
	ret[1] = sqrtf(base[1] * light[1]);
	ret[2] = sqrtf(base[2] * light[2]);
	ret[3] = sqrtf(base[3] * light[3]);
	i = (ret[3] << 24) + (ret[2] << 16) + (ret[1] << 8) + (ret[0] << 0);
	i = apply_mult_2(i, d);
	return (i);
}

static float			specular(t_light light,
				t_vec cam, t_vec collide)
{
	float				specular;
	t_point				l;
	t_point				v;
	t_point				r;

	l = sub_vec(collide.origin, light.origin);
	v = cam.direction;
	r = sub_vec(mult_vec2(collide.direction,
		dot_product(collide.direction, l) * 2), l);
	r = normalize(r);
	specular = powf(dot_product(r, v), 13);
	return (specular);
}

static int			create_specular(t_data *data, int color, t_ray *r, float dot)
{
	color = apply_mult(color, data->screen.preview.light.color, dot);
	dot = specular(data->screen.preview.light, data->screen.preview.cam, r->tmp);
	color = data->screen.preview.sphere.effect.color;
	if (dot > 0.0)
		color = apply_mult_3(data->screen.preview.light.color, color, dot);
	return (color);
}

int			switchcolor(int h)
{
	int		color;

	if (h > 0 && h < 121)
	{
		color = (h * 255 / 120) << 8; // B
		color += (255 - ((color & 0xFF00) >> 8)); // G
	}
	else if (h < 241)
	{
		color = ((h - 120) * 255 / 120) << 16; // R
		color += (255 - ((color & 0xFF0000) >> 16)) << 8; //G
	}
	else
	{
		color = ((h - 240) * 255) / 120; // G
		color += (255 - (color & 0xFF)) << 16; // R
	}
	return (color);
}

float	stay_in_case(float	value, float min, float max)
{
	if (value > min && value < max)
		return (value);
	return (value < min ? min : max);
}


float			slider(t_data *data, t_slider *slider)
{
	if ((data->input.button & SDL_BUTTON_LEFT /*&& !(data->input.oldbuton & SDL_BUTTON_LEFT*/) && (hitbox(data->input.x, data->input.y, &slider->position)) == 1)
		slider->selected = 1;
	if (!(data->input.button & SDL_BUTTON_LEFT))
		slider->selected = 0;
	if (slider->selected == 1)
	{
		if (!slider->dir) /* X */
			slider->cursor.x = stay_in_case(data->input.x - (slider->cursor.w / 2.0), slider->position.x, slider->position.x + slider->position.w);
		else
			slider->cursor.y = stay_in_case(data->input.y - (slider->cursor.h / 2.0), slider->position.y, slider->position.y + slider->position.h);
	}
		// printf("%d\n", data->input.x);
		//slider horizontale
	// if ()
	// {
	// 	//slider verticale
	// }
	/*
		Quel direction du slider (x / y)?
		Slider Selectionner (en mouvement)?
		Return quel valeur ? (Position du curseur sur slider / User En mouvement sur slider)
	*/

	SDL_SetRenderDrawColor(data->window.rend, slider->colorbg & 0xFF, slider->colorbg & 0xFF00, slider->colorbg & 0xFF0000, slider->colorbg & 0xFF000000);
	SDL_RenderFillRect(data->window.rend, &slider->position);
	SDL_SetRenderDrawColor(data->window.rend, slider->colorcursor & 0xFF, slider->colorcursor & 0xFF00, slider->colorcursor & 0xFF0000, slider->colorcursor & 0xFF000000);
	SDL_RenderFillRect(data->window.rend, &slider->cursor);
	if (!slider->dir)
		return ((float)(slider->cursor.x - slider->position.x) / (slider->position.w));
	return ((float)(slider->cursor.y - slider->position.y) / (slider->position.h));
}

static	void	init_slider_preview(t_data *data)
{
	data->screen.preview.slider[0].init = 1;
	data->screen.preview.slider[0].dir = 0;
	data->screen.preview.slider[0].selected = 0;
	data->screen.preview.slider[0].colorbg = 0x7c7c7c;
	data->screen.preview.slider[0].colorcursor = 0xFF0000;
	data->screen.preview.slider[0].position.x = 0;
	data->screen.preview.slider[0].position.y = data->window.y - 80;
	data->screen.preview.slider[0].position.w = 200;
	data->screen.preview.slider[0].position.h = 25;
	data->screen.preview.slider[0].cursor.x = 95;
	data->screen.preview.slider[0].cursor.y = data->window.y - 80;
	data->screen.preview.slider[0].cursor.w = 10;
	data->screen.preview.slider[0].cursor.h = 25;
	/* Slider Vertical */
	data->screen.preview.slider[1].init = 1;
	data->screen.preview.slider[1].dir = 1;
	data->screen.preview.slider[1].selected = 0;
	data->screen.preview.slider[1].colorbg = 0x909090;
	data->screen.preview.slider[1].colorcursor = 0x000000;
	data->screen.preview.slider[1].position.x = 300 - 25 - 20;
	data->screen.preview.slider[1].position.y = 100;
	data->screen.preview.slider[1].position.w = 25;
	data->screen.preview.slider[1].position.h = data->window.y - 400;
	data->screen.preview.slider[1].cursor.x = 300 - 25 - 20;
	data->screen.preview.slider[1].cursor.y = 300;
	data->screen.preview.slider[1].cursor.w = 25;
	data->screen.preview.slider[1].cursor.h = 100;
}

void		new_rt(t_data *data)
{
	t_vec	ray;
	static	SDL_Rect	petit = {.x = 0, .y = 200, .w = 200, .h = 200};
	static	SDL_Rect	rect_slider = {.x = 0, .y = 0, .w = 200, .h = 25};
	static	SDL_Rect	slider_bar = {.x = 15, .y = 0, .w = 10, .h = 25};
	float	dist;
	t_point	new_point;
	t_point	l2n;
	float	dot;
	t_ray	r;
	int		color;
	void			*tmp;
	static float var = 0;
	static char flag = 0;

	printf("[%d]\n", slider_bar.x);
	(void)r;
	if (!data->screen.preview.slider[0].init)
		init_slider_preview(data);
	tmp = data->obj.item[data->obj.index[1]];
	var += 5;
	if (var > 350)
		var = 5;
	if (!data->hud.color_obj)
		data->screen.preview.sphere.effect.color = switchcolor((int)var);
	petit.y = data->window.y - 300;
	SDL_LockTexture(data->screen.preview.texture, NULL, &data->screen.preview.pxl, &data->window.pitch);
	if (!flag)
		data->screen.preview.light.origin.x -= 2;
	else
		data->screen.preview.light.origin.x += 2;
	if (data->screen.preview.light.origin.x < - 120)
		flag = 1;
	if (data->screen.preview.light.origin.x > 120)
		flag = 0;
	ray.origin = fill_vec(0, 0, 0);
	ray.origin.y = - (300 / 2.0);
	ray.direction = fill_vec(0, 0, 1);
	while (ray.origin.y < (300 / 2.0))
	{
		ray.origin.x = - (300 / 2.0);
		while (ray.origin.x < 300 / 2.0)
		{
			if ((dist = sphere(&data->screen.preview.sphere, ray)) != -1)
			{
				new_point = set_neworigin(ray, dist);
				l2n = normalize(sub_vec(new_point, data->screen.preview.light.origin));
				r.tmp.origin = veccpy(new_point);
				new_point = normalize(sub_vec(new_point, data->screen.preview.sphere.origin.origin));
				r.tmp.direction = veccpy(new_point);
				dot = dot_product(l2n, new_point);
				if (dot < 0)
				{
					//Specular
					color = data->screen.preview.sphere.effect.color;
					((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) + ((150 +(int)ray.origin.y) * 300)] = create_specular(data, color, &r, -dot);
				}
				else
					((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) + ((150 +(int)ray.origin.y) * 300)] = apply_mult_2(data->screen.preview.sphere.effect.color, 1 - dot);
			}
			else
				((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) + ((150 +(int)ray.origin.y) * 300)] = 0xFFFFFF; // Couleur du fond (interface)
			ray.origin.x += 1.0;
		}
		ray.origin.y += 1.0;
	}
	rect_slider.y = data->window.y - 80;
	slider_bar.y = data->window.y - 80;
	SDL_UnlockTexture(data->screen.preview.texture);
	SDL_RenderCopy(data->window.rend, data->screen.preview.texture, NULL, &petit);
	printf("=> %f\n", slider(data, &data->screen.preview.slider[0]));
	slider(data, &data->screen.preview.slider[1]);
	SDL_RenderPresent(data->window.rend);
	SDL_Delay(64);
}
