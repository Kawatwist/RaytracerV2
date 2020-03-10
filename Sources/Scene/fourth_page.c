/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fourth_page.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:24:56 by luwargni          #+#    #+#             */
/*   Updated: 2020/03/09 22:56:57 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		info_option(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("OPTION");
	print_text(data, tmp1 * 314.44, tmp2 * 202.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("CTRL for value negatif");
	print_text(data, tmp1 * 260.44, tmp2 * 227.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("J for reset cam");
	print_text(data, tmp1 * 260.44, tmp2 * 242.5, ((tmp1 + tmp2) * 11.7 / 2));
}

static void		info_effect(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("EFFECT");
	print_text(data, tmp1 * 314.44, tmp2 * 55.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup(" Page 4");
	print_text(data, tmp1 * 314.44, tmp2 * 440.5, ((tmp1 + tmp2) * 14.7 / 2));
	data->font.str = ft_strdup("KP 1 reflection");
	print_text(data, tmp1 * 260.44, tmp2 * 80.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("KP 2 refraction");
	print_text(data, tmp1 * 260.44, tmp2 * 95.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("KP 3 opacite");
	print_text(data, tmp1 * 260.44, tmp2 * 110.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press \".\" for bounce");
	print_text(data, tmp1 * 260.44, tmp2 * 125.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("press \"*\" for bounce 0");
	print_text(data, tmp1 * 260.44, tmp2 * 140.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("press G for rayon obj");
	print_text(data, tmp1 * 260.44, tmp2 * 155.5, ((tmp1 + tmp2) * 11.7 / 2));
}

void			fourth_page(t_data *data)
{
	float	tmp1;
	float	tmp2;

	tmp1 = (data->window.x / 500.0);
	tmp2 = (data->window.y / 500.0);
	info_effect(data, tmp1, tmp2);
	info_option(data, tmp1, tmp2);
}
