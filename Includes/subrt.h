/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subrt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:22:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/07 22:47:58 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBRT_H
# define SUBRT_H

# include "SDL2/SDL.h"

# define CAM_TXT "./texture/Texture/cam.tga"
# define SPHERE_TXT "./texture/Texture/sphere.tga"
# define LIGHT_TXT "./texture/Texture/light.tga"
# define HUD_TXT "./texture/Texture/overlay.tga"

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
	SDL_Rect		pos[10];
	SDL_Surface		*tmp;
	SDL_Texture		*texture[10];
	int				flag_icon;
	int				color_obj;
}					t_hud;

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Renderer	*rend;
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
	unsigned char	oldkey[282];
	int				x;
	int				y;
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

#endif
