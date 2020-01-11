#include "rt.h"

static void	stay_in_case(t_data *data)
{
	data->obj.index[0] >= data->obj.nb_camera ? data->obj.index[0] = 0 : 0;
	data->obj.index[0] < 0 ? data->obj.index[0] = data->obj.nb_camera - 1 : 0;
	data->obj.index[1] >= data->obj.nb_item ? data->obj.index[1] = 0 : 0;
	data->obj.index[1] < 0 ? data->obj.index[1] = data->obj.nb_item - 1 : 0;
	data->obj.index[2] >= data->obj.nb_light ? data->obj.index[2] = 0 : 0;
	data->obj.index[2] < 0 ? data->obj.index[2] = data->obj.nb_light - 1 : 0;

	data->obj.type_index > 2 ? data->obj.type_index = 0 : 0;
	data->obj.type_index < 0 ? data->obj.type_index = 2 : 0;
}

static void	input_obj(t_data *data)
{
	void		*tmp;
	void		**obj;
	static char	enter = 1;
	//Modif Index
	if (key_check(*data, SDL_SCANCODE_KP_ENTER))
		enter *= -1;
	if (key_check(*data, SDL_SCANCODE_KP_PLUS) && enter == 1)
		data->obj.index[data->obj.type_index] += 1;
	if (key_check(*data, SDL_SCANCODE_KP_MINUS) && enter == 1)
		data->obj.index[data->obj.type_index] -= 1;
	if (key_check(*data, SDL_SCANCODE_KP_PLUS) && enter != 1)
		data->obj.type_index += 1;
	if (key_check(*data, SDL_SCANCODE_KP_MINUS) && enter != 1)
		data->obj.type_index -= 1;
	// if (key_check(*data, SDL_SCANCODE_KP_PERIOD) && enter == 1)
	// 	data-> += 1;//mettre les bounce
	// else if (key_check(*data, SDL_SCANCODE_KP_PERIOD) && enter != 1)
	// 	data->obj.type_index -= 1;
	// Check > Nb_type
	stay_in_case(data);
	//Modif Obj
	//	data->obj.type_index ==> ptr sur function
	if (data->obj.type_index == 1)
		tmp = (data->obj.item[data->obj.index[1]]);
	else if (data->obj.type_index == 2)
		tmp = &(data->obj.light[data->obj.index[data->obj.type_index]]);
	else
		tmp = &(data->obj.camera[data->obj.index[data->obj.type_index]]);
	obj = &(tmp);
	data->move[data->obj.type_index] (data, obj);
}

void        input(t_data *data)
{
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	data->input.button = (int)SDL_GetMouseState(&data->input.x, &data->input.y);
	ft_memcpy(data->input.oldkey, data->input.key, 282);
	SDL_PollEvent(&data->input.ev);
    if (key_check(*data, SDL_SCANCODE_V))
		data->flag.pixel = (data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
	input_obj(data);
	light_cursor(data);
}