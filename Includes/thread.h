/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:49:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/29 16:34:57 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <subrt.h>
# include <object.h>
# include <pthread.h>
# include "rt.h"
# define ETIMEDOUT 110

typedef struct			s_args
{
	int					joined;
	pthread_t			td;
	pthread_mutex_t		mtx;
	pthread_cond_t		cond;
	void				**res;
}						t_args;

typedef	struct			s_thread
{
	void				*pxl;
	int					x;
	int					y;
	t_point				tmp_normal;
	t_flag				flag;
	t_object			obj;
	t_vec				ray;
	t_tga				**texture;
	t_tga				**normal;
	float				(*dist[7]) (void *obj, t_vec ray);
	t_point				(*txt[7]) (void *data, void *obj, t_vec ray,
							int choose);
	void				(*move[3]) (t_data *data, void **obj);
	int					ambiant;
	int					pos;
	int					percent;
	int					bounce;
	int					len;
	float				dist_ray;
	int					max_dist;
	pthread_mutex_t		mutex;
	char				signal;
	pthread_t			thd;
	int					tmp_color;
	char				loading;
	int					current;
	float				tile;
	t_point				perlin[GRADIENT * GRADIENT];
}						t_thread;
/*
**			Special Function pthread
**
**		Doesn't exit on macos (only linux)
**		Sources : https://kotaeta.com/54232697
**
**			Changed for the Norme
*/
int						pthread_timedjoin_np(pthread_t td, void **res,
							struct timespec *ts);
void					loading_bar(t_data *data);
void					setup_rect(t_data *data, SDL_Rect *og,
							SDL_Rect *screen, SDL_Rect *lolz);
void					loading_sc(t_data *data, int p);
void					light_variance(t_data *data, t_thread *thd);
/*
**			Special Effect
*/
t_point					find_refraction(t_thread *data, void *obj, t_vec ray);
t_point					find_reflexion(t_vec ray, t_thread *data);
/*
**			Textures
*/
int						find_perlin(t_thread *data, void *obj, t_vec ray);
int						find_damier(t_thread *data, void *obj, t_vec ray);
t_point					find_normal_with_txt(t_thread *data, void *object,
							t_vec collide);
int						find_size(t_thread data, void *obj, int choose);
t_point					find_normal_texture(t_thread data, void *obj,
							t_vec collide, t_point normal);
t_point					texture_obj(void *data,
							void *obj, t_vec ray, int choose);
t_point					texture_plan(void *data,
							void *obj, t_vec ray, int choose);
t_point					texture_sphere(void *data,
							void *obj, t_vec ray, int choose);
t_point					texture_cylinder(void *data,
							void *obj, t_vec ray, int choose);
t_point					texture_cone(void *data,
							void *obj, t_vec ray, int choose);
/*
**			Light
*/

unsigned int			diapo(t_thread *data, t_vec *ray,
							int index, int bounce);
int						mix(int i, int j);
int						apply_mult_3(int i, int j, float d);
int						apply_mult_2(int i, float d);
int						apply_mult(int i, int j, float d);
unsigned int			add_color(unsigned int base, unsigned int new);
int						light_color(unsigned int color, unsigned int newcolor);
int						create_specular(t_thread *data, t_ray *r,
							float dot, int index);
unsigned int			add_color(unsigned int base, unsigned int new);
unsigned int			spot(t_thread *data, t_ray r, int index);
unsigned int			omni(t_thread *data, t_ray r, int index);
unsigned int			ray_to_light(t_thread *data, t_ray r);
void					*check_object_light(t_thread *data,
							t_vec ray, float *dist, float max_dist);
void					*check_object(t_thread *data, t_vec ray,
							float *dist, void *ignore);
/*
**			Ray Setup
*/
t_vec					setup_refraction(t_thread *data,
							void *obj, t_vec ray, float dist);
t_vec					setup_opacity(t_thread *data,
							void *obj, t_vec ray, float dist);
t_vec					setup_reflection(t_thread *data, t_vec ray, float dist);
void					aa_render(t_thread *data, int *x, int *y, int *curr);
unsigned int			set_ambiant(unsigned int base, int divide);
int						load_modif(t_data *data, t_thread *tmp);
unsigned int			set_color(unsigned int base, unsigned int new,
						float percent, char a);
t_point					find_normal(void *object, t_vec collide);
t_point					find_normal_triangle(t_triangle *t);
unsigned int			find_color(t_thread *data, void *obj, t_vec ray);
unsigned int			send_ray(t_thread *data, t_vec ray,
							int bounce, void *ignore);
int						start_ray(t_thread *data);
/*
**			Memory
*/
int						setup_txt_and_normal(t_data *data, t_thread *tmp);
int						setup_obj(t_data *data, t_thread *tmp);
int						clear_thread(t_thread *data);
int						quitrequested(t_thread *data);


float			shadow(t_thread *data, t_ray r, int index);
#endif
