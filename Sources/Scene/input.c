#include "rt.h"

static void	stay_in_case(t_data *data)
{
	data->obj.index[0] > data->obj.nb_camera ? data->obj.index[0] = 0 : 0;
	data->obj.index[0] < 0 ? data->obj.index[0] = data->obj.nb_camera - 1 : 0;
	data->obj.index[1] > data->obj.nb_camera ? data->obj.index[1] = 0 : 0;
	data->obj.index[1] < 0 ? data->obj.index[1] = data->obj.nb_item - 1 : 0;
	data->obj.index[2] > data->obj.nb_camera ? data->obj.index[2] = 0 : 0;
	data->obj.index[2] < 0 ? data->obj.index[2] = data->obj.nb_light - 1 : 0;
}

static void	input_obj(t_data *data)
{
	//Modif Index
	if (key_check(*data, SDL_SCANCODE_EQUALS))
		data->obj.index[data->obj.type_index] += 1;
	if (key_check(*data, SDL_SCANCODE_MINUS))
		data->obj.index[data->obj.type_index] -= 1;
	// Check > Nb_type
	stay_in_case(data);
	//Modif Obj
	
	//	data->obj.type_index ==> ptr sur function
			// Cam Function
			// item Function
			// Light Function
}

void        input(t_data *data)
{
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	ft_memcpy(data->input.oldkey, data->input.key, 200);
	SDL_PollEvent(&data->input.ev);
    if (key_check(*data, SDL_SCANCODE_Q))
		data->flag.pixel = (data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
	input_obj(data);
}