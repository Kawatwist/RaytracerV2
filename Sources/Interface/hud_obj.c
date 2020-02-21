/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:55:26 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/19 17:00:46 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	hud_triangle(t_data *data)
{
	data->hud.pos[7].x = data->window.x / 80.0;
	data->hud.pos[7].y = data->window.y / 1.112;
	data->hud.pos[7].w = (data->window.x / 500.0) * 35.0;
	data->hud.pos[7].h = (data->window.y / 500.0) * 35.0;
}

void	hud_cylinder(t_data *data)
{
	data->hud.pos[6].x = data->window.x / 80.0;
	data->hud.pos[6].y = data->window.y / 1.112;
	data->hud.pos[6].w = (data->window.x / 500.0) * 35.0;
	data->hud.pos[6].h = (data->window.y / 500.0) * 35.0;
}

void	hud_cone(t_data *data)
{
	data->hud.pos[5].x = data->window.x / 80.0;
	data->hud.pos[5].y = data->window.y / 1.112;
	data->hud.pos[5].w = (data->window.x / 500.0) * 35.0;
	data->hud.pos[5].h = (data->window.y / 500.0) * 35.0;
}

void	hud_plan(t_data *data)
{
	data->hud.pos[4].x = data->window.x / 80.0;
	data->hud.pos[4].y = data->window.y / 1.112;
	data->hud.pos[4].w = (data->window.x / 500.0) * 35.0;
	data->hud.pos[4].h = (data->window.y / 500.0) * 35.0;
}

void	hud_sphere(t_data *data)
{
	data->hud.pos[3].x = data->window.x / 80.0;
	data->hud.pos[3].y = data->window.y / 1.112;
	data->hud.pos[3].w = (data->window.x / 500.0) * 35.0;
	data->hud.pos[3].h = (data->window.y / 500.0) * 35.0;
}
