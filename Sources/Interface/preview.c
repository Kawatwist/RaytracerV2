/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:05:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/24 20:55:55 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			init_preview(t_data *data)
{
	data->screen.preview.light = fill_vec(0, -120, 350);
	data->obj.light[0].color = 0xFFFFFF;
	data->screen.preview.cam.origin = fill_vec(0, 0, 0);
	data->screen.preview.cam.direction = normalize(fill_vec(0, 0, 1));
	data->screen.preview.sphere.origin.origin = fill_vec(0, 0, 300);
	data->screen.preview.sphere.rayon = 20.0;
	data->screen.preview.sphere.effect.color = 0x0000FF;
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
	float	specular;
	t_point				l;
	t_point				v;
	t_point				r;
	static int			test = 0;
	static float		value = 3;

	test++;
	if (test == 50000)
		test = 0;
	if (!test)
		value += 0.0;
	if (value == 20)
		value = 1;
	l = sub_vec(collide.origin, light.origin);
	v = cam.direction;
	r = sub_vec(mult_vec2(collide.direction,
		dot_product(collide.direction, l) * 2), l);
	r = normalize(r);
	specular = powf(dot_product(r, v), value);
	return (specular);
}

static int			create_specular(t_data *data, int color, t_ray *r, float dot, int index)
{
	(void)r;
	(void)index;
	(void)data;

	if (dot > 0.0)
	{
	printf("%d\n", ((t_base *)r->obj)->effect.color);// savoir quoi mettre a la place de "((t_base *)r->obj)->effect.color"
	exit(0);
		color = apply_mult(((t_base *)r->obj)->effect.color, data->obj.light[index].color, dot);
		dot = specular(data->obj.light[index], data->screen.preview.cam, r->tmp);
		if (dot > 0.0)
			color = apply_mult_3(data->obj.light[index].color, color, dot);
	}
	return (color);
}

void		new_rt(t_data *data)
{
	t_vec	ray;
	static	float	val = 100.0;
	static	SDL_Rect	petit = {.x = 0, .y = 300, .w = 300, .h = 300};
	float	dist;
	t_point	new_point;
	t_point	l2n;
	float	dot;
	t_ray	r;
	int		color;

	(void)r;
	(void)color;

	petit.y = data->window.y - 300;
	SDL_RenderClear(data->window.rend);
	SDL_LockTexture(data->screen.preview.texture, NULL, &data->screen.preview.pxl, &data->window.pitch);
	/*RT*/
	data->screen.preview.light.y -= 1;
	data->screen.preview.light.z -= 1;
	if (data->screen.preview.light.y < - 400)//bouger light
		data->screen.preview.light.y = - 120;
	data->screen.preview.sphere.rayon = val;
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
				l2n = normalize(sub_vec(new_point, data->screen.preview.light));
				new_point = normalize(sub_vec(new_point, data->screen.preview.sphere.origin.origin));
				dot = dot_product(l2n, new_point);
				if (dot >= 0)
				{
					//Specular
					((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) + ((150 +(int)ray.origin.y) * 300)] = (Uint8)(255.0 * (1 -dot)) << 0;
					color = create_specular(data, 0xFFFFFF, &r, dot, 0);
					// printf("%d\n", color);
					// ((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) + ((150 +(int)ray.origin.y) * 300)] = color;
				}
				else
					((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) + ((150 +(int)ray.origin.y) * 300)] = data->screen.preview.sphere.effect.color;
			}
			else
				((int *)data->screen.preview.pxl)[(150 + (int)ray.origin.x) + ((150 +(int)ray.origin.y) * 300)] = 0x0;
			ray.origin.x += 1.0;
		}
		ray.origin.y += 1.0;
	}
	SDL_UnlockTexture(data->screen.preview.texture);
	SDL_RenderCopy(data->window.rend, data->screen.preview.texture, NULL, &petit);
	SDL_RenderPresent(data->window.rend);
	SDL_Delay(64);
}
