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
	unsigned char	oldkey[282];
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
    t_light			*light;
	t_camera		*camera;
    int             nb_item;
	int				nb_light;
	int             nb_camera;
	char			**texture;
	char			**normal;
	int             nb_texture;
	int             nb_normal;
	int	            index[3];
	int         	type_index;
}                   t_object;

typedef struct      s_ray
{
	t_vec			tmp;
    unsigned int	color[2];
	void			*obj;
	float			dist[2];
	int				bounce;
}                   t_ray;

typedef struct      s_scene
{
    int             fd;
}                   t_scene;

#endif