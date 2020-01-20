/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:49:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/20 21:54:10 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "subrt.h"
# include <pthread.h> 

typedef	struct 		s_thread
{
	t_object		obj;
	unsigned int	color;
}					t_thread;

#endif