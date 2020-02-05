/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:49:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/05 01:13:53 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "subrt.h"
# include <pthread.h>
# include "rt.h"

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
	float				(*dist[5]) (void *obj, t_vec ray);
	t_point				(*txt[5]) (void *data, void *obj, t_vec ray,
							int choose);
	void				(*move[3]) (t_data *data, void **obj);
	float				ambiant;
	int					pos;
	int					percent;
	int					bounce;
	int					len;
	pthread_t			thd;
}						t_thread;

/*
**			Special Effect
*/
t_point					find_refraction(t_thread data, void *obj, t_vec ray);
t_point					find_reflexion(void *obj, t_vec ray, t_thread data);
/*
**			Textures
*/
t_point					find_normal_with_txt(t_thread data, void *object,
							t_vec collide);
int						find_size(t_thread data, void *obj, int choose);
t_point					find_normal_texture(t_thread data, void *obj,
							t_vec collide, t_point normal);
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
unsigned int			ray_to_light(t_thread *data, t_vec ray,
							t_vec tmp, int base);
void					*check_object_light(t_thread *data,
							t_vec ray, float *dist);
void					*check_object(t_thread *data, t_vec ray,
							float *dist);
/*
**			Ray Setup
*/
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

#endif
