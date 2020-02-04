/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:58:10 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/02 06:24:11 by lomasse          ###   ########.fr       */
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

# define TRUE 1
# define XSCREEN 1000
# define YSCREEN 1000

typedef struct	s_flag
{
	Uint32		pixel : 2;
	Uint32		perspective : 1;
	Uint32		bounce : 1;
	Uint32		refresh : 1;
	Uint32		filter : 2;
	Uint32		antialiasing : 2;
}				t_flag;

typedef struct s_data	t_data;

struct			s_data
{
	t_window			window;
	t_input				input;
	t_object			obj;
	t_scene				parse;
	t_flag				flag;
	t_vec				ray;
	t_tga				**texture;
	t_tga				**normal;
	float				(*dist[5]) (void *obj, t_vec ray);
	t_point				(*txt[5]) (void *data, void *obj, t_vec ray, int choose);
	void				(*move[3]) (t_data *data, void **obj);
	int					percent;
	int					bounce;
	int					ambiant;
	void				*thread;
};

float			sphere_depth(void *sphere, t_vec ray);
/*
**			Collide Object
*/
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
t_point			rotx(t_point origin, float ang);
t_point			roty(t_point origin, float ang);
t_point			rotz(t_point origin, float ang);
t_point			set_neworigin_neg(t_vec ray, float distance);
t_point			set_neworigin_op(t_vec ray, float distance);
t_point			set_neworigin(t_vec ray, float distance);
t_point			veccpy(t_point pnt);
t_vec			create_vec(t_point origin, t_point direction);
t_point			fill_vec(float x, float y, float z);
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
void			move_obj(t_data *data, void **obj);
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
void			create_screenshot(t_data *data, void *pxl);
/*
**			Thread
*/
void			*thread_function(void	*arg);
int				thread_poll(t_data *data);
int     		start_thread(t_data *data);
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
int				initialize(t_data *data);
/*
**			Basic
*/
int				main(int argc, char *argv[]);
int				loop(t_data data);
void			super_sample(t_data *data, int x, int y);
int				clear_memory(t_data *data);
int				stop_main_execute(char *error, t_data *data, int error_value);
void			stop_execute(char *error, t_data *data);

#endif
