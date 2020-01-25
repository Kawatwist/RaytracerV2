/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:49:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/25 20:57:24 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "subrt.h"
# include <pthread.h>
# include "rt.h"

typedef	struct			s_thread
{
/*
**			T_Window
**	Care About Pxl (Need to Set everycycle)
*/ 
	void				*pxl;
	int					x;
	int					y;
/*
**			T_flag
*/
	t_flag				flag;
/*
**			Other
**	Ray's Vector Will be set everysubcycle
**	Mutex for texture and normal ?
*/
	t_object			obj;
	t_vec				ray;
	t_tga				**texture;
	t_tga				**normal;
	float				(*dist[4]) (void *obj, t_vec ray);
	t_point				(*txt[4]) (void *data, void *obj, t_vec ray, int choose);
	void				(*move[3]) (t_data *data, void **obj);
/*
**	Need to Be Refresh like pxl
*/
	int					pos;
	int					percent;
	int					bounce;
	int					len;
/*
**			Thread's heart
*/
	pthread_t			thd;
}					t_thread;

/*
**			Special Effect
*/
t_point			find_refraction(t_thread data, void *obj, t_vec ray);
t_point			find_reflexion(void *obj, t_vec ray, t_thread data);
/*
**			Textures
*/
t_point			find_normal_with_txt(t_thread data, void *object, t_vec collide);
int				find_size(t_thread data, void *obj, int choose);
t_point			find_normal_texture(t_thread data, void *obj,
					t_vec collide, t_point normal);
t_point			texture_plan(void *data,
					void *obj, t_vec ray, int choose);
t_point			texture_sphere(void *data,
					void *obj, t_vec ray, int choose);
t_point			texture_cylinder(void *data,
					void *obj, t_vec ray, int choose);
t_point			texture_cone(void *data,
					void *obj, t_vec ray, int choose);
/*
**			Light
*/
unsigned int	ray_to_light(t_thread *data, t_vec ray, t_vec tmp, int base);
void			*check_object_light(t_thread *data, t_vec ray, float *dist);
void			*check_object(t_thread *data, t_vec ray, float *dist);
/*
**			Ray Setup
*/
int     		load_modif(t_data *data, t_thread *tmp);
unsigned int	set_color(unsigned int base, unsigned int new, float percent);
t_point			find_normal(void *object, t_vec collide);
unsigned int	find_color(t_thread *data, void *obj, t_vec ray);
unsigned int	send_ray(t_thread *data, t_vec ray, int bounce);
int				start_ray(t_thread *data);

#endif