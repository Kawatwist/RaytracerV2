/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:52:33 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/05 21:00:55 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_origin(t_data *data, float tmp1, float tmp2, int index)
{
	if (index == 0)
	{
		data->font.str = ft_itoa(data->obj.camera[data->obj.index[0]].pos.origin.x);
		print_text(data, tmp1 * 472.5, tmp2 * 376.0, ((tmp1 + tmp2) * 16.7 / 2));
		data->font.str = ft_itoa(data->obj.camera[data->obj.index[0]].pos.origin.y);
		print_text(data, tmp1 * 472.5, tmp2 * 402.0, ((tmp1 + tmp2) * 16.7 / 2));
		data->font.str = ft_itoa(data->obj.camera[data->obj.index[0]].pos.origin.z);
		print_text(data, tmp1 * 472.5, tmp2 * 429.0, ((tmp1 + tmp2) * 16.7 / 2));
	}
	if (index == 1)
	{
		data->font.str = ft_itoa(((t_base *)data->obj.item[data->obj.index[1]])->origin.origin.x);
		print_text(data, tmp1 * 472.5, tmp2 * 376.0, ((tmp1 + tmp2) * 16.7 / 2));
		data->font.str = ft_itoa(((t_base *)data->obj.item[data->obj.index[1]])->origin.origin.y);
		print_text(data, tmp1 * 472.5, tmp2 * 402.0, ((tmp1 + tmp2) * 16.7 / 2));
		data->font.str = ft_itoa(((t_base *)data->obj.item[data->obj.index[1]])->origin.origin.z);
		print_text(data, tmp1 * 472.5, tmp2 * 429.0, ((tmp1 + tmp2) * 16.7 / 2));
	}
	if (index == 2)
	{
		data->font.str = ft_itoa(data->obj.light[data->obj.index[2]].origin.x);
		print_text(data, tmp1 * 472.5, tmp2 * 376.0, ((tmp1 + tmp2) * 16.7 / 2));
		data->font.str = ft_itoa(data->obj.light[data->obj.index[2]].origin.y);
		print_text(data, tmp1 * 472.5, tmp2 * 402.0, ((tmp1 + tmp2) * 16.7 / 2));
		data->font.str = ft_itoa(data->obj.light[data->obj.index[2]].origin.z);
		print_text(data, tmp1 * 472.5, tmp2 * 429.0, ((tmp1 + tmp2) * 16.7 / 2));
	}
}

static void	color_hud_obj(t_data *data, t_effect tmp)
{
	data->hud.pos[9].w = (data->window.x / 500.0) * 10.0;
	data->hud.pos[9].x = data->window.x / 10.7;
	data->hud.pos[9].h = ((tmp.color & 0xFF0000) >> 16) * data->window.y / 2100;
	data->hud.pos[9].y = data->window.y - data->hud.pos[9].h;
	data->hud.pos[10].w = (data->window.x / 500.0) * 10.0;
	data->hud.pos[10].x = data->window.x / 8.6;
	data->hud.pos[10].h = ((tmp.color & 0xFF00) >> 8) * data->window.y / 2100;
	data->hud.pos[10].y = data->window.y - data->hud.pos[10].h;
	data->hud.pos[11].w = (data->window.x / 500.0) * 10.0;
	data->hud.pos[11].x = data->window.x / 7.2;
	data->hud.pos[11].h = ((tmp.color & 0xFF) >> 0) * data->window.y / 2100;
	data->hud.pos[11].y = data->window.y - data->hud.pos[11].h;
}

static void	set_cam(t_data *data, float tmp1, float tmp2)
{
	data->hud.pos[0].x = data->window.x / 80.0;
	data->hud.pos[0].y = data->window.y / 1.112;
	data->hud.pos[0].w = (data->window.x / 500.0) * 35.0;
	data->hud.pos[0].h = (data->window.y / 500.0) * 35.0;
	data->font.str = ft_itoa(data->obj.index[0]);
	print_text(data, tmp1 * 469.44, tmp2 * 473.5, ((tmp1 + tmp2) * 16.7 / 2));
	set_origin(data, tmp1, tmp2, 0);
}

static int	set_obj(t_data *data, float tmp1, float tmp2)
{
	t_effect	tmp;

	tmp = ((t_base *)data->obj.item[data->obj.index[1]])->effect;
	if (tmp.type == SPHERE)
		hud_sphere(data);
	else if (tmp.type == PLAN)
		hud_plan(data);
	else if (tmp.type == CONE)
		hud_cone(data);
	else if (tmp.type == CYLINDER)
		hud_cylinder(data);
	else if (tmp.type == TRIANGLE)
		hud_triangle(data);
	color_hud_obj(data, tmp);
	data->font.str = ft_itoa(data->obj.index[1]);
	print_text(data, tmp1 * 469.44, tmp2 * 473.5, ((tmp1 + tmp2) * 16.7 / 2));
	set_origin(data, tmp1, tmp2, 1);
	return (tmp.type);
}

static void	set_light(t_data *data, float tmp1, float tmp2)
{
	int		tmp;

	tmp = data->obj.light[data->obj.index[2]].color;
	data->hud.pos[2].x = data->window.x / 80.0;
	data->hud.pos[2].y = data->window.y / 1.112;
	data->hud.pos[2].w = (data->window.x / 500.0) * 35.0;
	data->hud.pos[2].h = (data->window.y / 500.0) * 35.0;
	data->hud.pos[9].w = (data->window.x / 500.0) * 10.0;
	data->hud.pos[9].x = data->window.x / 10.7;
	data->hud.pos[9].h = ((tmp & 0xFF0000) >> 16) * data->window.y / 2100;
	data->hud.pos[9].y = data->window.y - data->hud.pos[9].h;
	data->hud.pos[10].w = (data->window.x / 500.0) * 10.0;
	data->hud.pos[10].x = data->window.x / 8.6;
	data->hud.pos[10].h = ((tmp & 0xFF00) >> 8) * data->window.y / 2100;
	data->hud.pos[10].y = data->window.y - data->hud.pos[10].h;
	data->hud.pos[11].w = (data->window.x / 500.0) * 10.0;
	data->hud.pos[11].x = data->window.x / 7.2;
	data->hud.pos[11].h = ((tmp & 0xFF) >> 0) * data->window.y / 2100;
	data->hud.pos[11].y = data->window.y - data->hud.pos[11].h;
	data->font.str = ft_itoa(data->obj.index[2]);
	print_text(data, tmp1 * 469.44, tmp2 * 473.5, ((tmp1 + tmp2) * 16.7 / 2));
	set_origin(data, tmp1, tmp2, 2);
}

void		set_section(t_data *data)
{
	float	tmp1;
	float	tmp2;

	tmp1 = (data->window.x / 500.0);
	tmp2 = (data->window.y / 500.0);
	if (data->obj.type_index == 0)
	{
		set_cam(data, tmp1, tmp2);
		data->hud.pos[9].w = 0;
		data->hud.pos[9].x = 0;
		data->hud.pos[9].h = 0;
		data->hud.pos[9].y = 0;
		data->hud.pos[10].w = 0;
		data->hud.pos[10].x = 0;
		data->hud.pos[10].h = 0;
		data->hud.pos[10].y = 0;
		data->hud.pos[11].w = 0;
		data->hud.pos[11].x = 0;
		data->hud.pos[11].h = 0;
		data->hud.pos[11].y = 0;
	}
	if (data->obj.type_index == 1)
		data->hud.type_obj = set_obj(data, tmp1, tmp2) + 3;
	if (data->obj.type_index == 2)
		set_light(data, tmp1, tmp2);
}
