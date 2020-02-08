/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:19:41 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/08 08:16:48 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point	find_pos(t_data *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	return (ret);
}

static void		add_light(t_data *data, t_light *new, int x, int y)
{
	new->color = 0xFFFFFF;
	new->distance = 5;
	new->intensity = 1;
	new->origin = find_pos(data, x, y);
}

void			light_cursor(t_data *data)
{
	static char	curr = 0;
	int			i;

	if (data->input.button & SDL_BUTTON_LEFT)
	{
		i = -1;
		while (++i < 4)
		{
			if (curr == 0)
			{
				add_light(data, &(((t_thread *)data->thread)[i].obj.light[data->obj.nb_light - 1]),
				data->input.x, data->input.y);
				// ((t_thread *)data->thread)[i].obj.nb_light += 1;
			}
			else
				((t_thread *)data->thread)[i].obj.light[data->obj.nb_light].origin =
				find_pos(data, data->input.x, data->input.y);
		}
		curr == 0 ? curr = 1 : 0;
	}
	else if (curr == 1)
	{
		// i = -1;
		// while (++i < 4)
		// 	((t_thread *)data->thread)[i].obj.nb_light -= 1;
		curr = 0;
	}
}
