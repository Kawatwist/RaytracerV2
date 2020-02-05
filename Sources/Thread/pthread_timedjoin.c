/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_timedjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 04:09:42 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/05 04:44:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void *waiter(void *ap)
{
	t_args	*args;

	args = (t_args *)ap;
	pthread_join(args->td, args->res);
	pthread_mutex_lock(&args->mtx);
	args->joined = 1;
	pthread_mutex_unlock(&args->mtx);
	pthread_cond_signal(&args->cond);
	return 0;
}

int pthread_timedjoin_np(pthread_t td, void **res, struct timespec *ts)
{
	pthread_t	tmp;
	int			ret;
	t_args		args;
	Uint32		time;

	time = SDL_GetTicks();
	args.td = td;
	args.res = res;
	args.joined = 0;
	pthread_mutex_init(&args.mtx, 0);
	pthread_cond_init(&args.cond, 0);
	pthread_mutex_lock(&args.mtx);
	ret = pthread_create(&tmp, 0, waiter, &args);
	while (!args.joined && ret != ETIMEDOUT)
	{
		ret = pthread_cond_timedwait(&args.cond, &args.mtx, ts);
		if ((SDL_GetTicks() - time) > ts->tv_nsec)
			ret = ETIMEDOUT;
		SDL_Delay(1);
	}
	pthread_mutex_unlock(&args.mtx);
	pthread_cancel(tmp);
	pthread_join(tmp, 0);
	pthread_cond_destroy(&args.cond);
	pthread_mutex_destroy(&args.mtx);
	return (args.joined ? 0 : ETIMEDOUT);
}
