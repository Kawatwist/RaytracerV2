/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:45:33 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/25 16:44:50 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		init_case(t_data *data, int mode)
{
	int i;

	if (mode == 0)
		if (!(data->all_button = (t_case *)malloc(sizeof(t_case) * CASE_NBR)))
			return (1);
	i = -1;
	while (++i < CASE_NBR)
		button_stand(data, i);
	button_once_refresh(data);
	button_aa(data);
	button_normals(data);
	button_quality(data);
	button_show(data);
	button_diapo(data);
	button_slider_filter(data);
	button_slider_bounce(data);
	button_advance(data);
	return (0);
}

int		click_button_is_in_menu(t_data *data)
{
	if (data->input.x <= 300 && data->input.y <= data->window.y * 0.55
	&& data->input.button != data->input.oldbutton
	&& data->input.button == 1)
		return (1);
	else
		return (0);
}

void	click_button(t_data *data)
{
	int start;
	int val;
	int blabla;
	int max_val;

	start = (int)(data->screen.preview.slider[1].value * CASE_NBR);
	if (click_button_is_in_menu(data) == 1)
	{
		if (data->input.y >= 95 && data->input.x >= 245
		&& data->input.x <= 245 + 30)
		{
			blabla = (data->input.y) / 45 - 2;
			data->input.y = data->input.y % 45;
			if (data->input.y > 6 && data->input.y < 41)
				if (blabla + start < CASE_NBR)
				{
					max_val = data->all_button[blabla + start].i;
					if (max_val < 1)
						max_val = 1;
					val = (data->input.x - 245) / (30 / max_val);
					data->all_button[blabla + start].pf(data, val + 1);
				}
		}
	}
}
