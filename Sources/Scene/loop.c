#include "rt.h"

int			loop(t_data data)
{
	data.flag.pixel = 2;
	data.obj.type_index = 2;
	while (TRUE)
	{
		input(&data);
		if (data.input.key[SDL_SCANCODE_ESCAPE] || SDL_QuitRequested())
			break ;
		SDL_LockTexture(data.window.txt, NULL, &data.window.pxl, &data.window.pitch);
		if (start_ray(&data))
			return (10);
		data.percent++;
		if (data.percent > 99)
			data.percent = 0;
		SDL_UnlockTexture(data.window.txt);
		SDL_Delay(10);
		SDL_RenderCopy(data.window.rend, data.window.txt, NULL, NULL);
		SDL_RenderPresent(data.window.rend);
	}
	return (0);
}