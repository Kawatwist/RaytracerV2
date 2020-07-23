/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fade_color_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:08:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 23:40:10 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		lowest_value(int color)
{
	if ((color & 0xFF) < ((color & 0xFF00) >> 8) &&
		(color & 0xFF) < ((color & 0xFF0000) >> 16))
		return (color & 0xFF);
	if ((color & 0xFF) > ((color & 0xFF00) >> 8) &&
		((color & 0xFF00) >> 8) < ((color & 0xFF0000) >> 16))
		return ((color & 0xFF00) >> 8);
	return ((color & 0xFF0000) >> 16);
}

int		highest_value(int color)
{
	if ((color & 0xFF) > ((color & 0xFF00) >> 8) &&
		(color & 0xFF) > ((color & 0xFF0000) >> 16))
		return (color & 0xFF);
	if ((color & 0xFF) < ((color & 0xFF00) >> 8) &&
		((color & 0xFF00) >> 8) > ((color & 0xFF0000) >> 16))
		return ((color & 0xFF00) >> 8);
	return ((color & 0xFF0000) >> 16);
}
