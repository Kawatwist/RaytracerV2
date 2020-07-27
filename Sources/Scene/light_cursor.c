/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:19:41 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/27 15:47:14 by anboilea         ###   ########.fr       */
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

static	t_point	side_pos(t_data *data)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x,
		data->window.x * 0.3));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y,
		data->window.y * 0.3));
	return (ret);
}

static void		add_light(t_data *data, t_light *new, int x, int y)
{
	new->color = 0xFFFFFF;
	new->distance = 5;
	new->intensity = 1;
	new->type = 1;
	new->ang = 0.5;
	new->direction = normalize(sub_vec(find_pos(data, x, y),
		data->obj.camera[data->obj.index[0]].pos.origin));
	new->origin = side_pos(data);
}

void			light_cursor(t_data *data)
{
	int			i;
	t_object	*obj;

	i = -1;
	if (data->input.button & SDL_BUTTON_LEFT && ((data->hud.flag_hud == 0) ||
	(data->hud.flag_hud == 1 && data->input.x > 300 && data->input.y > 20)))
		while (++i < 4)
		{
			add_light(data,
				&(((t_thread *)data->thread)[i].obj.light[data->obj.nb_light]),
				data->input.x, data->input.y);
		}
	else
		while (++i < 4)
		{
			obj = &((t_thread *)data->thread)[i].obj;
			obj->light[data->obj.nb_light].color = 0;
			obj->light[data->obj.nb_light].distance = 0;
			obj->light[data->obj.nb_light].intensity = 0;
			obj->light[data->obj.nb_light].type = 0;
			obj->light[data->obj.nb_light].ang = 0;
			obj->light[data->obj.nb_light].origin = fill_vec(0, 0, 0);
			obj->light[data->obj.nb_light].direction = fill_vec(0, 0, 0);
		}
}
