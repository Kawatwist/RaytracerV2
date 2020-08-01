/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:38:04 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/01 14:25:21 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

# include <rt.h>

float			sphere_depth(void *sphere, t_vec ray);
/*
**			Collide Object
*/
float			box_(t_plan p, t_vec ray, t_point diff, Uint8 side);
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

int     		parsing_torus(t_data *data, char **old, char *line);
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
int				other(t_data *data, char **line, int index);
int				add_point(t_data *data, char **line, int index);
int				fill_effect(t_effect *effect, char *line);
int				add_texture_face(t_data *data, char **line, int index);
int				parsing_obj(t_data *data, char **line, char *type);
int				parsing_camera(t_data *data, char **line);
int				parsing_head(t_data *data, char **line);
int				parsing(t_data *data, int nb, char *arg[]);
int				check_parse(t_data *data);
int				fill_texture(t_data *data, char *line);
t_point			normal_face(Uint8 face);
int				fill_normal(t_data *data, char *line);
/*
**			Loop
*/
void			set_background(t_data *data);
void			draw_outline(t_data *data);
void			draw_outline_color(t_data *data);
void			draw_title_background(t_data *data);
void			draw_background_box(t_data *data, int y);
void			draw_separation(t_data *data, SDL_Rect dst, int nb, int x);
void			draw_button_ext_0(t_data *data,
					SDL_Rect *dst, unsigned int color);
void			draw_button_ext_1(t_data *data,
					SDL_Rect dst, unsigned int color);
void			draw_button_ext_2(t_data *data,
					SDL_Rect dst, unsigned int color);
void			draw_button_ext_3(t_data *data,
					SDL_Rect dst, unsigned int color);
int				texture_on_screen_ext(t_data *data, SDL_Rect dst);
/*
**			Event's
*/
char			mouse_hold(t_data *data, Uint32 mask);
char			mouse_check(t_data *data, Uint32 mask);
char			key_hold(t_data *data, Uint32 mask);
char			key_check(t_data *data, Uint32 mask);
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
t_point			cam_rot(t_point origin, float ang, t_point axe);
t_quat			quat_prod(t_quat a, t_quat b);
t_quat			quat_conj(t_quat a);
/*
**			Tools
*/
unsigned int	maxu(unsigned int value, unsigned int value2);
unsigned int	lowu(unsigned int value, unsigned int value2);
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
void			check_folder_screenshot(void);
void			create_screenshot_bmp(t_data *data, void *pxl,
					char **path, int mode);
void			create_screenshot(t_data *data, void *pxl);
char			*finddirname(void);
char			*findcurrentdirname(void);
void			framed(t_data *data);
void			show_framed(t_data *data);
/*
**			Thread
*/
void			check_mutex(t_data *data);
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
int				init_cam(t_data *data);
int				initialize_cam(t_data *data);
int				initialize_sdl(t_data *data);
int				initialize_scene(t_data *data);
void			window_render(t_data *data);
int				initialize(t_data *data);
int				init_case(t_data *data, int mode);
void			initialize_cam_ext(t_data *data, int index);
void			preset_cam_ext(t_data *data, int index, float coef);

void			init_slider_preview(t_data *data);
/*
**			Font
*/
int				print_text(t_data *data, int x, int y, int size);
SDL_Rect		set_font_pos(char a);
int				init_font(t_data *data);
/*
**			Basic
*/
void			ask_screenshot(t_data *data);
void			resize(t_data *data);
int				real_time_icon(t_data *data);
int				set_icone(t_data *data);
int				loading(t_data *data);
int				main(int argc, char *argv[]);
int				loop(t_data *data);
int				single_screen(t_data *data);
int				flag(t_data *data, int argc, char **argv);
void			flag_help(int page);
void			super_sample(t_data *data, int x, int y);
int				clear_memory(t_data *data);
void			clear_texture_main(t_data *data, t_tga **tofree);
void			clear_normal_main(t_data *data, t_tga **tofree);
void			destroy_text_main(SDL_Texture *t);
int				stop_main_execute(char *error, t_data *data, int error_value);
int				stop_execute(char *error, t_data **data);
/*
**			Interface
*/
t_point			color_to_pos(int posx, int posy, int color);
t_circle		setup_circle(t_point pos, int color, long int radius,
				void *pxl);
float			find_slider_pos(int color);
int				switchcolor(int h);
int				find_color_chroma(int i, int j);
int				hue(t_data *data, int color);
void			color_picker(t_data *data);
void			draw_circle(t_circle circle);
char			*input_hud_text(t_data*data, char *text);
void			interface_grey(t_data *data);
int				texture_on_screen(t_data *data);
void			get_input(t_data *data);
int				home_screen(t_data *data);
int				info_screen(t_data *data);
int				sub_loop(t_data *data);
void			draw_rect(t_data *ptr, SDL_Rect dst, unsigned int color);
void			create_menu_texture(t_data *data);
int				init_preview(t_data *data);
void			mini_rt(t_data *data);
void			new_rt(t_data *data);
float			slider(t_data *data, t_slider *slider);
void			draw_button(t_data *data, int x, int y, t_case c);
void			draw_background_box(t_data *data, int y);
char			*input_hud_text(t_data *data, char *text);
void			boo_value_diapo(t_data *data, int val);
void			boo_value_normals(t_data *data, int val);
void			boo_value_show(t_data *data, int val);
void			boo_value_aa(t_data *data, int val);
void			boo_value_quality(t_data *data, int val);
void			boo_value_refresh(t_data *data, int val);
void			boo_value_alpha(t_data *data, int val);
void			button_alpha(t_data *data);
void			show_button(t_data *data);
void			show_txt(t_data *data);
void			click_button(t_data *data);
void			video_settings(t_data *data);
void			draw_nbvideo_bg(t_data *data);
void			button_normals(t_data *data);
void			boo_value_normals(t_data *data, int val);
void			boo_value_show(t_data *data, int val);
void			button_show(t_data *data);
void			boo_value_quality(t_data *data, int val);
void			button_quality(t_data *data);
void			boo_value_aa(t_data *data, int val);
void			button_aa(t_data *data);
void			boo_value(t_data *data, int val);
void			button_stand(t_data *data, int i);
void			boo_value_diapo(t_data *data, int val);
void			button_diapo(t_data *data);
void			boo_value_refresh(t_data *data, int val);
void			button_once_refresh(t_data *data);
void			button_advance(t_data *data);
void			button_slider_filter(t_data *data);
void			button_slider_bounce(t_data *data);
void			draw_slider(t_data *data, int y, int selector);

/*
**			Post Processing
*/

void			perlin_noise(t_data *data);
void			init_perlin(t_point uv, t_perl *p);
void			init_perlin_wood(t_point uv, t_perl *p);
void			init_grad(t_point uv, t_perl *p, t_grad *g);
float			get_perlin_cloud(t_point perlin[GRADIENT * GRADIENT],
					t_point uv, int type);
float			get_perlin_marble(t_point perlin[GRADIENT * GRADIENT],
					t_point uv);
float			get_perlin_wood(t_point perlin[GRADIENT * GRADIENT],
					t_point uv);
int				perlin_color_wood(float val);
int				perlin_color_cloud(float val);
int				perlin_color_marble(float val);
void			generate_perlin(t_data *data);
void			generate_marble(float (*marble)[GRADIENT * GRADIENT]);
void			generate_wood(float (*wood)[GRADIENT * GRADIENT]);
void			cartoon(t_data *data, unsigned int i, int tr, int tg);
int				post_processing(t_data *data);
void			filter_negatif(t_data *data, unsigned int i);

void			create_rgb_txt(t_data *data);
int				pics_on_screen(t_data *data);

int				hitbox(int	x, int	y, SDL_Rect *pos);
int				create_specular_mini(t_data *data, int color,
					t_ray *r, float dot);
int				mix_mini(int i, int j);

int				lowest_value(int color);
int				highest_value(int color);

void			rot_cam_axe(int key_code, t_camera *tmp, t_point tmp2);
void			call_rot_cam(t_data *data);
void			input_obj(t_data *data);
void			get_input(t_data *data);
void			button_shadow(t_data *data);
void			button_ambiant(t_data *data);

#endif
