/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:49:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 20:03:12 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "subrt.h"
# include <pthread.h> 
# include "rt.h" 

typedef	struct 		s_thread
{
	pthread_t			thd;
	t_object			obj;
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	// pthread_attr_t		signal;
	t_vec				ray;
	void				*pxl;
	t_data				data;
	int					x;
	int					y;
	int					index;
	int					bounce;
	unsigned int		len;
}					t_thread;

#endif