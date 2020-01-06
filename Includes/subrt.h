#ifndef SUBRT_H
# define SUBRT_H

# include "SDL2/SDL.h"

typedef struct      s_window
{
    SDL_Window      *window;
    SDL_Renderer    *rend;
    SDL_Texture     *txt;
    void            *pxl;
    int             pitch;
    int             xscreen;
    int             yscreen;
}                   t_window;

typedef struct      s_calc
{
    float           a;
    float           b;
    float           c;
    float           delta;
    float           sqt;
}                   t_calc;

typedef struct      s_input
{
    SDL_Event       ev;
	unsigned char	*key;
	unsigned char	oldkey[200];
    int             x;
    int             y;
    int             button;
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
    void			**item;
    int             nb_item;
    t_light			*light;
	int				nb_light;
	t_camera		*camera;
	int             nb_camera;
	char			**texture;
	int             nb_texture;
	int	            index[3];
	int         	type_index;
}                   t_object;

typedef struct      s_scene
{
    int             fd;
}                   t_scene;

#endif