#include "rt.h"

int			initialize_sdl(t_data *data)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	data->window.window = SDL_CreateWindow("Rt", 200, 200, 200, 200, SDL_WINDOWSHOWN);
	if (data->window.window == NULL)
		return (1);
	data->window.rend = SDL_CreateRenderer(data->window.window,
			-1, SDL_RENDERER_ACCELERATED)
	if (data->window.rend == NULL)
		return (2);
	return (0);
}