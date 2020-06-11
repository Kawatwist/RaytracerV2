/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:49:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/11 18:23:03 by lomasse          ###   ########.fr       */
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
	int					max_dist;
	pthread_mutex_t		mutex;
	char				signal;
	pthread_t			thd;
	int					tmp_color;
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
/*
**			Special Effect
*/
t_point					find_refraction(t_thread data, void *obj, t_vec ray);
t_point					find_reflexion(void *obj, t_vec ray, t_thread data);
/*
**			Textures
*/
int						find_damier(t_thread *data, void *obj, t_vec ray);
t_point					find_normal_with_txt(t_thread data, void *object,
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

int						light_color(unsigned int color, unsigned int newcolor);
int						create_specular(t_thread *data, int color, t_ray *r, float dot);
unsigned int			ray_to_light(t_thread *data, t_ray r);
void					*check_object_light(t_thread *data,
							t_vec ray, float *dist, float max_dist);
void					*check_object(t_thread *data, t_vec ray,
							float *dist);
/*
**			Ray Setup
*/
t_vec					setup_refraction(t_thread *data, void *obj, t_vec ray, float dist);
t_vec		setup_opacity(t_thread *data, void *obj, t_vec ray, float dist);
t_vec					setup_reflection(t_thread *data, void *obj, t_vec ray, float dist);
void					aa_render(t_thread *data, int *x, int *y, int *curr);
unsigned int			set_ambiant(unsigned int base);
int						load_modif(t_data *data, t_thread *tmp);
unsigned int			set_color(unsigned int base, unsigned int new,
						float percent, char a);
t_point					find_normal(void *object, t_vec collide);
t_point					find_normal_triangle(t_triangle *t);
unsigned int			find_color(t_thread *data, void *obj, t_vec ray);
unsigned int			send_ray(t_thread *data, t_vec ray, int bounce);
int						start_ray(t_thread *data);
/*
**			Memory
*/
int						setup_txt_and_normal(t_data *data, t_thread *tmp);
int						setup_obj(t_data *data, t_thread *tmp);
int						clear_thread(t_thread *data);

#endif
