#include "rt.h"

void        input(t_data *data)
{
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	ft_memcpy(data->input.oldkey, data->input.key, 200);
	SDL_PollEvent(&data->input.ev);
    if (key_check(*data, SDL_SCANCODE_Q))
		data->flag.pixel = (data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
}