/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_page.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:23:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/28 12:43:56 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		info_textures(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("TEXTURES");
	print_text(data, tmp1 * 94.44, tmp2 * 300.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("KP 4 id texture");
	print_text(data, tmp1 * 50.44, tmp2 * 325.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("KP 5 id textures normal");
	print_text(data, tmp1 * 50.44, tmp2 * 340.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("KP 6 trouver truc a faire");
	print_text(data, tmp1 * 50.44, tmp2 * 355.5, ((tmp1 + tmp2) * 11.7 / 2));
}

static void		info_color(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("COLOR");
	print_text(data, tmp1 * 94.44, tmp2 * 142.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup("KP 7 color red");
	print_text(data, tmp1 * 50.44, tmp2 * 167.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("KP 8 color green");
	print_text(data, tmp1 * 50.44, tmp2 * 182.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("KP 9 color blue");
	print_text(data, tmp1 * 50.44, tmp2 * 197.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("1 2 3 4 for filters");
	print_text(data, tmp1 * 50.44, tmp2 * 212.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press click gauche for");
	print_text(data, tmp1 * 50.44, tmp2 * 237.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("create light in cursor");
	print_text(data, tmp1 * 50.44, tmp2 * 252.5, ((tmp1 + tmp2) * 11.7 / 2));
}

static void		info_quality(t_data *data, float tmp1, float tmp2)
{
	data->font.str = ft_strdup("QUALITY");
	print_text(data, tmp1 * 94.44, tmp2 * 55.5, ((tmp1 + tmp2) * 16.7 / 2));
	data->font.str = ft_strdup(" Page 3");
	print_text(data, tmp1 * 94.44, tmp2 * 440.5, ((tmp1 + tmp2) * 14.7 / 2));
	data->font.str = ft_strdup("Press O for antialiasing");
	print_text(data, tmp1 * 50.44, tmp2 * 80.5, ((tmp1 + tmp2) * 11.7 / 2));
	data->font.str = ft_strdup("Press V for quality");
	print_text(data, tmp1 * 50.44, tmp2 * 95.5, ((tmp1 + tmp2) * 11.7 / 2));
}

void			third_page(t_data *data)
{
	float	tmp1;
	float	tmp2;

	tmp1 = (data->window.x / 500.0);
	tmp2 = (data->window.y / 500.0);
	info_quality(data, tmp1, tmp2);
	info_color(data, tmp1, tmp2);
	info_textures(data, tmp1, tmp2);
}
