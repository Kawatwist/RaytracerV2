/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subrt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:22:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/07 02:16:42 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBRT_H
# define SUBRT_H

# include "SDL2/SDL.h"
# include <object.h>

# define CAM_TXT "./texture/Texture/cam.tga"
# define SPHERE_TXT "./texture/Texture/sphere.tga"
# define LIGHT_TXT "./texture/Texture/light.tga"
# define HUD_TXT "./texture/Texture/overlay.tga"
# define CYLINDER_TXT "./texture/Texture/cylinder.tga"
# define TRINITY_TXT "./texture/Texture/trinity.tga"
# define CONE_TXT "./texture/Texture/cone.tga"
# define PLAN_TXT "./texture/Texture/plan.tga"
# define OEIL_TXT "./texture/Texture/Oeil.tga"

typedef enum		e_lol
{
	HOME,
	NOFILE,
	RUN,
	INFO,
}					t_lol;

typedef enum		e_hud
{
	CAM_LOGO = 0,
	LIGHT_LOGO = 1,
	SPHERE_LOGO = 2,
	PLAN_LOGO = 4,
	CYLINDER_LOGO = 5,
	CONE_LOGO = 6,
	HUD = 7,
	HOME_SCREEN = 8,
	LOAD_SCREEN = 9,
}					e_hud;

typedef struct		s_c33
{
	Uint32			color;
	Uint32			flag : 1;
}					t_c33;

typedef struct		s_hud
{
	SDL_Rect		pos[12];
	SDL_Surface		*tmp;
	SDL_Texture		*texture[12];
	SDL_Texture		*rgb[3];
	int				color_obj;
	int				type_obj;
	Uint8			flag_hud : 1;
	Uint8			last_hud : 1;
}					t_hud;

typedef struct		s_load
{
	SDL_Texture		*load;
	SDL_Texture		*loading;
	SDL_Texture		*lolz;
}					t_load;

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Renderer	*rend;
	SDL_Texture		*oldtxt;
	SDL_Texture		*txt;
	void			*pxl;
	int				pitch;
	unsigned int	x;
	unsigned int	y;
}					t_window;

typedef struct		s_calc
{
	float			a;
	float			b;
	float			c;
	float			delta;
	float			sqt;
	float			t0;
	float			t1;
}					t_calc;

typedef struct		s_input
{
	SDL_Event		ev;
	unsigned char	*key;
	unsigned char	*rkey;
	unsigned char	oldkey[282];
	int				x;
	int				y;
	int				oldbutton;
	int				button;
}					t_input;

typedef struct		s_camera
{
	t_vec			pos;
	t_point			sc;
	t_point			x;
	t_point			y;
	t_vec			oldpos;
	t_point			oldsc;
	t_point			oldx;
	t_point			oldy;
}					t_camera;

typedef struct		s_object
{
	void			**item;
	t_light			*light;
	t_camera		*camera;
	int				nb_item;
	int				nb_light;
	int				nb_camera;
	char			**texture;
	char			**normal;
	int				nb_texture;
	int				nb_normal;
	int				index[3];
	int				type_index;
	Uint32			color_find[2];
}					t_object;

typedef struct		s_ray
{
	t_vec			tmp;
	unsigned int	color[2];
	void			*obj;
	float			dist[2];
	int				bounce;
}					t_ray;

typedef struct		s_scene
{
	int				fd;
	unsigned int	error_line;
}					t_scene;

typedef struct	s_menu
{
	SDL_Texture		*background;
}				t_menu;
typedef struct    	s_grad
{
    int ix;
    int iy;
    float x;
    float y;
}      				 t_grad;

typedef struct      s_perl
{
    int x0;
    int x1;
    int y0;
    int y1;
    float sx;
    float sy;
    float n0;
    float n1;
    float ix0;
    float ix1;
    float value;
}      				t_perl;

typedef struct		s_slider
{
	Uint32			colorbg;
	Uint32			colorcursor;
	SDL_Rect		position;
	SDL_Rect		cursor;
	Uint32			init : 1;
	Uint32			dir : 1;
	Uint32			selected : 1;
}					t_slider;

typedef struct		s_color_picker
{
	Uint32			circle;
	SDL_Rect		position;
}					t_color_picker;

typedef struct		s_preview
{
	t_vec			cam;
	t_sphere		sphere;
	SDL_Texture		*texture;
	void			*pxl;
	t_light			light;
	t_slider		slider[2];
	t_color_picker	color_picker;
}					t_preview;

#endif
