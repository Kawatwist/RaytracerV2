/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_slider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:49:48 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/25 17:03:37 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	button_slider_filter(t_data *data)
{
	data->all_button[5].to_print = "Filter";
	data->all_button[5].val = data->flag.filter;
	data->all_button[5].type = 1;
}

void	button_slider_bounce(t_data *data)
{
	data->all_button[6].to_print = "Bounce";
	data->all_button[6].val = data->flag.bounce;
	data->all_button[6].type = 1;
}

void	draw_slider(t_data *data, int y, int selector)
{
	data->screen.preview.slider[selector].position.y = y + 8;
	data->screen.preview.slider[selector].cursor.y = y + 8;
	data->screen.preview.slider[selector].value = slider(data, &data->screen.preview.slider[selector]);
	if (selector == 2 && data->screen.preview.slider[selector].init == 1)
		data->flag.filter = data->screen.preview.slider[selector].value * 8;
	else if (selector == 3 && data->screen.preview.slider[selector].init == 1)
		data->bounce =
		(unsigned int)(data->screen.preview.slider[selector].value * 22);
}
