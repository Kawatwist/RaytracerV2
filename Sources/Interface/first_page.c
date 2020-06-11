/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_page.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:15:35 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/28 12:38:05 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		info_summary(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("SUMMARY");
	print_text(data, tmp1 * 94.44, tmp2 * 55.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup(" Page 1");
	print_text(data, tmp1 * 94.44, tmp2 * 440.5, ((tmp1 + tmp2) * 14.7 / 2));
	data->font.str = ft_strdup("1  Summary");
	print_text(data, tmp1 * 50.44, tmp2 * 95.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("2  Hud");
	print_text(data, tmp1 * 50.44, tmp2 * 125.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("2  Move");
	print_text(data, tmp1 * 50.44, tmp2 * 155.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("3  HD");
	print_text(data, tmp1 * 50.44, tmp2 * 185.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("3  Color");
	print_text(data, tmp1 * 50.44, tmp2 * 215.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("3  Textures");
	print_text(data, tmp1 * 50.44, tmp2 * 245.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("3  Normale");
	print_text(data, tmp1 * 50.44, tmp2 * 275.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("4  Effect");
	print_text(data, tmp1 * 50.44, tmp2 * 305.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("4  Option");
	print_text(data, tmp1 * 50.44, tmp2 * 335.5, ((tmp1 + tmp2) * 16.7 / 2));
}

void			first_page(t_data *data)
{
	float	tmp1;
	float	tmp2;

	tmp1 = (data->window.x / 500.0);
	tmp2 = (data->window.y / 500.0);
	info_summary(data, tmp1, tmp2);
}
