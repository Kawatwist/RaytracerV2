/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:58:10 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/30 19:39:07 by anboilea         ###   ########.fr       */
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

typedef struct	s_flag
{
	Uint32		pixel : 2;
	Uint32		perspective : 1;
	Uint32		bounce : 1;
	Uint32		refresh : 1;
	Uint32		asked : 1;
	Uint32		filter : 3;
	Uint32		antialiasing : 2;
	Uint32		first : 1;
	Uint32		time : 1;
	Uint32		diapo : 1;
	Uint32		flare : 1;
	Uint32		video : 12;
	Uint32		nb_video : 12;
	Uint32		show : 1;
	Uint32		save : 1;
}				t_flag;

typedef struct s_data	t_data;

typedef struct		s_interface
{
	SDL_Texture		*(scenetxt[4]);
	char			interface;
	int				(*screen[4]) (t_data *data);
	unsigned int	page;
}					t_interface;

typedef struct	s_font
{
	SDL_Texture		*font_maj;
	SDL_Texture		*font;
	SDL_Rect		pos;
	char			*str;
}				t_font;

struct			s_data
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
	t_point				perlin[GRADIENT * GRADIENT];
};

float			sphere_depth(void *sphere, t_vec ray);
/*
**			Collide Object
*/
float			obj(void *obj, t_vec ray);
float			disk(void *di, t_vec ray);
float			triangle(void *tri, t_vec ray);
float			cone(void *coo, t_vec ray);
float			cylinder(void *cylinder, t_vec ray);
float			plane(void *plane, t_vec ray);
float			sphere(void *sphere, t_vec ray);
/*
**			Parsing
*/
int				parsing_light(t_data *data, char **old, char *line);
t_point			get_point(char *str);
t_point			get_point_y(char *str);
int				parsing_files(t_data *data, char *line);
int				create_light(t_data *data);
int				create_camera(t_data *data);
int				create_normal(t_data *data);
int				create_texture(t_data *data);
int				create_item(t_data *data);
int				find_type(char *type);
int				create_type(t_data *data, int index, int type);
int				fill_obj(t_data *data, char **line, int index);
int				parsing_obj(t_data *data, char **line, char *type);
int				parsing_camera(t_data *data, char **line);
int				parsing_head(t_data *data, char **line);
int				parsing(t_data *data, int nb, char *arg[]);
int				check_parse(t_data *data);
int				fill_texture(t_data *data, char *line);
t_point			normal_face(Uint8 face);
int				fill_normal(t_data *data, char *line);
/*
**			Event's
*/
char			key_old(t_data data, int mask);
char			key_check(t_data data, int mask);
void			input(t_data *data);
/*
**			Move Vec
*/
void			rot_cam_video(t_data *data, t_camera *cam);
t_point			rotx(t_point origin, float ang);
t_point			roty(t_point origin, float ang);
t_point			rotz(t_point origin, float ang);
t_point			set_neworigin_neg(t_vec ray, float distance);
t_point			set_neworigin_op(t_vec ray, float distance);
t_point			set_neworigin(t_vec ray, float distance);
t_point			veccpy(t_point pnt);
t_vec			create_vec(t_point origin, t_point direction);
t_point			fill_vec(float x, float y, float z);
t_point			add_vec2(t_point v1, float sub);
t_point			add_vec(t_point v1, t_point v2);
t_point			sub_vec2(t_point v1, float sub);
t_point			sub_vec(t_point v1, t_point v2);
t_point			mult_vec2(t_point v1, float mult);
t_point			normalize(t_point v1);
t_point			neg_norm(t_point v1);
t_point			sqrt_vec(t_point v1);
t_point			mult_vec(t_point v1, t_point v2);
t_point			div_vec(t_point v1, t_point v2);
t_point			div_vec2(t_point v1, float div);
t_point			cross_vec(t_point v1, t_point v2);
float			cross_product(double **mat, t_point v1, int row);
float			dot_product(t_point v1, t_point v2);
float			length(t_point v1);
/*
**			Tools
*/
float			square(float f);
float			ang(float value);
float			rad(float value);
Uint32			set_bit(Uint32 var, Uint32 mask);
float			get_dot_abs(t_point v1, t_point v2);
float			get_angle_vec(t_point v1, t_point v2);
float			square(float f);
/*
**			Input
*/
void			move_cam(t_data *data, void **obj);
void			input_move_cam(t_data *data, t_point tmp, void **cam);
void			call_rot_cam(t_data *data);
void			mv_obj(t_data *data, t_obj **obj);
void			move_obj(t_data *data, void **obj);
void			mv_triangle(t_data *data, t_triangle **obj);
void			input_hud(t_data *data);
void			input_filter(t_data *data);
void			input_move_obj(t_data *data, void **obj);
void			input_color_obj(t_data *data, void **obj, char ctrl);
void			input_descartes_obj(t_data *data, void **obj, char ctrl);
void			input_id(t_data *data, void **obj, char ctrl);
void			input_textures(t_data *data, void **obj, char ctrl);
void			move_light(t_data *data, void **obj);
void			input_move_light(t_data *data, void **light);
void			input_color_light(t_data *data, void **light, char ctrl);
void			input_distance_light(t_data *data, void **light, char ctrl);
void			input_intensity_light(t_data *data, void **light, char ctrl);
void			light_cursor(t_data *data);
void			create_screenshot_bmp(t_data *data, void *pxl, char **path, int mode);
void			create_screenshot(t_data *data, void *pxl);
void			framed(t_data *data);
void			show_framed(t_data *data);
/*
**			Thread
*/
void			*thread_function(void	*arg);
int				thread_poll(t_data *data);
int				start_thread(t_data *data);
void			reset_item(t_object base, t_object *dest);
int				get_thread(t_data *data);
int				init_thread_memory(t_data *data);
/*
**			Initialize
*/
void			rot_init_cam_x(t_data *data, t_point *base,
					t_point *direction, int index);
void			rot_init_cam_y(t_data *data, t_point *base,
					t_point *direction, int index);
void			rot_init_cam_z(t_data *data, t_point *base,
					t_point *direction, int index);
int				initialize_cam(t_data *data);
int				initialize_sdl(t_data *data);
int				initialize_scene(t_data *data);
int				initialize(t_data *data);
/*
**			Font
*/
int				print_text(t_data *data, int x, int y, int size);
SDL_Rect		set_font_pos(char a);
int				init_font(t_data *data);
/*
**			Basic
*/
void			resize(t_data *data);
int				real_time_icon(t_data *data);
int				set_icone(t_data *data);
int				loading(t_data *data);
int				main(int argc, char *argv[]);
int				loop(t_data *data);
void			super_sample(t_data *data, int x, int y);
int				clear_memory(t_data *data);
int				stop_main_execute(char *error, t_data *data, int error_value);
int				stop_execute(char *error, t_data **data);
/*
**			Interface
*/
void			get_input(t_data *data);
int				home_screen(t_data *data);
int				info_screen(t_data *data);
int				sub_loop(t_data *data);
void			draw_rect(t_data *ptr, SDL_Rect dst, unsigned int color);
void			create_menu_texture(t_data *data);
/*
**			Run
*/
/*
**			Post Processing
*/

void			perlin_noise(t_data *data);
float   		get_perlin(t_point perlin[GRADIENT * GRADIENT], t_point uv);
void			generate_perlin(t_data *data);
int				post_processing(t_data *data);
int				init_hud(t_data *data);
void			set_hud(t_data *data);

void			create_rgb_txt(t_data *data);
int				pics_on_screen(t_data *data);
void			set_section(t_data *data);
void			hud_triangle(t_data *data);
void			hud_cylinder(t_data *data);
void			hud_cone(t_data *data);
void			hud_plan(t_data *data);
void			hud_sphere(t_data *data);

void			info_book(t_data *data, SDL_Rect *pos);
void			first_page(t_data *data);
void			second_page(t_data *data);
void			third_page(t_data *data);
void			fourth_page(t_data *data);
int				hitbox(int	x, int	y, SDL_Rect *pos);//mettre autre part




#endif
