#ifndef SUBRT_H
# define SUBRT_H

# include "SDL2/SDL.h"

typedef struct      s_window
{
    SDL_Window      *window;
    SDL_Renderer    *rend;
    void            *pxl;
    int             xscreen;
    int             yscreen;
}                   t_window

typedef struct      s_input
{
    SDL_Event       ev;
}                   t_input;

typedef struct		s_camera
{
	t_vec			pos;
	t_point			sc;
	t_point			x;
	t_point			y;
}					t_camera;

typedef struct      s_object
{
    void			*item;
    void			*light;
	t_camera		camera;
}                   t_object;

#endif