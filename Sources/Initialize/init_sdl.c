#include "rt.h"

int			initialize_sdl(t_data *data)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	data->window.window = SDL_CreateWindow("Rt", 0, 0, 400, 400, SDL_WINDOW_SHOWN);
	if (data->window.window == NULL)
		return (1);
	data->window.rend = SDL_CreateRenderer(data->window.window,
			-1, SDL_RENDERER_ACCELERATED);
	if (data->window.rend == NULL)
		return (2);
	data->window.txt = SDL_CreateTexture(data->window.rend, SDL_PIXELFORMAT_ABGR32, SDL_TEXTUREACCESS_STREAMING, 400, 400);
	if (data->window.txt == NULL)
		return (3);
	SDL_PollEvent(&data->ev);
	SDL_RenderPresent(data->window.rend);
	data->window.xscreen = 400;
	data->window.yscreen = 400;
	return (0);
}