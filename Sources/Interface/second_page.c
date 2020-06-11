/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_page.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:05:17 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/28 12:45:30 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		info_moves(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("MOVES");
	print_text(data, tmp1 * 314.44, tmp2 * 225.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("Press A for move left");
	print_text(data, tmp1 * 260.44, tmp2 * 250.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press W for move in");
	print_text(data, tmp1 * 260.44, tmp2 * 265.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press S for move back");
	print_text(data, tmp1 * 260.44, tmp2 * 280.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press D for move right");
	print_text(data, tmp1 * 260.44, tmp2 * 295.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press SPACE for move up");
	print_text(data, tmp1 * 260.44, tmp2 * 320.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press SHIFT for move down");
	print_text(data, tmp1 * 260.44, tmp2 * 335.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Arrow left for rot left");
	print_text(data, tmp1 * 260.44, tmp2 * 360.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Arrow up for rot up");
	print_text(data, tmp1 * 260.44, tmp2 * 375.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Arrow down for rot down");
	print_text(data, tmp1 * 260.44, tmp2 * 390.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Arrow right for rot right");
	print_text(data, tmp1 * 260.44, tmp2 * 405.5, ((tmp1 + tmp2) * 11.7 / 2));
}

static void		info_hud(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("  HUD");
	print_text(data, tmp1 * 314.44, tmp2 * 55.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup(" Page 2");
	print_text(data, tmp1 * 314.44, tmp2 * 440.5, ((tmp1 + tmp2) * 14.7 / 2));
	data->font.str = ft_strdup("Press H for hud display");
	print_text(data, tmp1 * 260.44, tmp2 * 80.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press KpEnter for");
	print_text(data, tmp1 * 260.44, tmp2 * 115.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("select a section");
	print_text(data, tmp1 * 260.44, tmp2 * 129.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press plusETmoin for");
	print_text(data, tmp1 * 260.44, tmp2 * 164.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("move between sections");
	print_text(data, tmp1 * 260.44, tmp2 * 178.5, ((tmp1 + tmp2) * 11.7 / 2));
}

void			second_page(t_data *data)
{
	float	tmp1;
	float	tmp2;

	tmp1 = (data->window.x / 500.0);
	tmp2 = (data->window.y / 500.0);
	info_hud(data, tmp1, tmp2);
	info_moves(data, tmp1, tmp2);
}
