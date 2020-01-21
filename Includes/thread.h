/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:49:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/21 23:18:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "subrt.h"
# include <pthread.h> 

typedef	struct 		s_thread
{
	pthread_t			thd;
	t_object			obj;
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	pthread_attr_t		signal;
	void				*pxl;
	int					x;
	int					y;
	int					index;
	unsigned int		len;
}					t_thread;

#endif