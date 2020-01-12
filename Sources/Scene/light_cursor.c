#include "rt.h"

static	t_point	find_pos(t_data *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[0].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	return (ret);
}

static void	create_light(t_data *data, t_light *new, int x, int y)
{
	new->color = 0xFFFFFF;
	new->distance = 2.5;
	new->intensity = 1;
	new->origin = find_pos(data, x, y);
}


void		light_cursor(t_data *data)
{
	static char curr = 0;
	if (data->input.button & SDL_BUTTON_LEFT)
	{
		if (curr == 0)
		{
			create_light(data, &data->obj.light[data->obj.nb_light], data->input.x, data->input.y);
			data->obj.nb_light += 1;
			curr = 1;
		}
		else
		{
			data->obj.light[data->obj.nb_light - 1].origin = find_pos(data,data->input.x, data->input.y);
		}
	}
	else if (curr == 1)
	{
		data->obj.nb_light -= 1;
		curr = 0;
	}
}