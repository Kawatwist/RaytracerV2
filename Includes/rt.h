/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:58:10 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/23 21:30:22 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "tga_reader.h"
# include "object.h"
# include "subrt.h"
# include "menu.h"

# define TRUE 1
# define PATH "./Texture/\0"
# define THREAD_SIG SIGTERM
# define THREAD_ALIVE 1
# define NOTHREAD 0
# define XSCREEN 1000
# define YSCREEN 1000
# define GRADIENT 64

# include "prototype.h"

typedef struct			s_flag
{
	Uint32				pixel : 2;
	Uint32				perspective : 1;
	Uint32				bounce : 1;
	Uint32				refresh : 1;
	Uint32				asked : 1;
	Uint32				filter : 3;
	Uint32				antialiasing : 2;
	Uint32				first : 1;
	Uint32				time : 1;
	Uint32				diapo : 1;
	Uint32				flare : 1;
	Uint32				cam_move : 1;
	Uint32				video : 12;
	Uint32				nb_video : 12;
	Uint32				show : 1;
	Uint32				save : 1;
	Uint32				normal : 1;
	Uint32				screen : 1;
	Uint32				typing : 1;
	Uint32				shadow : 1;
	Uint32				tile : 1;
	Uint32				icon : 1;
	Uint32				parsing : 1;
}						t_flag;

typedef struct			s_interface
{
	SDL_Texture			*(scenetxt[4]);
	char				interface;
	int					(*screen[4]) (t_data *data);
	t_preview			preview;
}						t_interface;

typedef struct			s_font
{
	SDL_Texture			*font_maj;
	SDL_Texture			*font;
	SDL_Rect			pos;
	char				*str;
}						t_font;

struct					s_data
{
	t_window			window;
	t_interface			screen;
	t_input				input;
	t_object			obj;
	t_scene				parse;
	t_menu				menu;
	t_hud				hud;
	t_flag				flag;
	t_vec				ray;
	t_font				font;
	t_load				load;
	t_tga				**texture;
	t_tga				**normal;
	t_case				*all_button;
	float				(*dist[7]) (void *obj, t_vec ray);
	t_point				(*txt[7]) (void *data, void *obj,
							t_vec ray, int choose);
	void				(*move[3]) (t_data *data, void **obj);
	int					percent;
	char				loading;
	int					bounce;
	int					ambiant;
	void				*thread;
	int					max_dist;
	int					argc;
	float				tile;
	t_point				perlin[GRADIENT * GRADIENT];
};
#endif
