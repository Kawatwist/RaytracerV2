/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subrt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:45:56 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/25 12:11:34 by lomasse          ###   ########.fr       */
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

# define CASE_NBR 15

typedef enum		e_lol
{
	HOME,
	NOFILE,
	RUN,
	INFO,
}					t_lol;

typedef enum		e_hudpage
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
}					t_hudpage;

typedef struct s_data	t_data;

typedef struct		s_c33
{
	Uint32			color;
	Uint32			flag : 1;
}					t_c33;

typedef struct		s_case
{
	void			(*pf)(t_data *, int);
	char			*to_print;
	int				val;
	char			i;
	int				type;
}					t_case;

typedef struct		s_select
{
	Uint32			index_last;
	Uint32			color_save;
	Uint32			color_pick_save;
	Uint32			selector : 1;
	Uint32			color_pick : 1;
}					t_select;

typedef struct		s_hud
{
	t_select		select;
	SDL_Rect		pos[12];
	SDL_Surface		*tmp;
	SDL_Texture		*texture[12];
	SDL_Texture		*rgb[3];
	int				type_obj;
	int				var;
	Uint8			last_color_obj : 1;
	Uint8			color_obj : 1;
	Uint8			flag_hud : 1;
	Uint8			last_hud : 1;
}					t_hud;

typedef struct		s_load
{
	SDL_Texture		*load;
	SDL_Texture		*loading;
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
	float			dot;
	float			len;
	float			rayon;
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

typedef struct s_camera	t_camera;

struct				s_camera
{
	t_vec			pos;
	t_vec			oldpos;
	t_point			sc;
	t_point			x;
	t_point			y;
	t_point			oldsc;
	t_point			oldx;
	t_point			oldy;
	t_point			axerot;
	t_camera		*stereo;
	Uint32			mode : 2;
};

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
	Uint32			good : 1;
}					t_ray;

typedef struct		s_scene
{
	int				fd;
	unsigned int	error_line;
}					t_scene;

typedef struct		s_menu
{
	SDL_Texture		*background;
}					t_menu;

typedef struct		s_grad
{
	int				ix;
	int				iy;
	float			x;
	float			y;
}					t_grad;

typedef struct		s_slider
{
	Uint32			colorbg;
	Uint32			colorcursor;
	SDL_Rect		position;
	SDL_Rect		cursor;
	Uint32			init : 1;
	Uint32			dir : 1;
	Uint32			selected : 1;
	float			value;
}					t_slider;

typedef struct		s_circle
{
	int				x;
	int				y;
	void			*pxl;
	int				r_outside;
	int				r_inside;
	int				color;
}					t_circle;

typedef struct		s_preview
{
	t_vec			cam;
	t_sphere		sphere;
	SDL_Texture		*texture;
	void			*pxl;
	t_light			light;
	t_slider		slider[4];
}					t_preview;

typedef struct		s_perl
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	float			sx;
	float			sy;
	float			n0;
	float			n1;
	float			ix0;
	float			ix1;
	float			value;
	float			xperiod;
	float			yperiod;
	float			turbpower;
	float			turbsize;
	float			xyvalue;
	float			xvalue;
	float			yvalue;
	float			sinvalue;
	float			distvalue;
}					t_perl;

#endif
