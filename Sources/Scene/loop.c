#include "rt.h"

int			loop(t_data data)
{
	while (TRUE)
	{
		SDL_LockTexture(data.window.txt, NULL, &data.window.pxl, &data.window.pitch);
		if (start_ray(&data))
			return (10);
		if (SDL_QuitRequested())
			break ;
		data.percent++;
		if (data.percent > 99)
			data.percent = 0;
		SDL_UnlockTexture(data.window.txt);
		SDL_RenderCopy(data.window.rend, data.window.txt, NULL, NULL);
		SDL_RenderPresent(data.window.rend);
		SDL_Delay(16);
	}
	return (0);
}