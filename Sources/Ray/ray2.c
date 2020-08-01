/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:54:01 by cbilga            #+#    #+#             */
/*   Updated: 2020/08/01 18:31:32 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static t_point	normal_sub(t_vec ray, void *obj)
{
	if (((t_base *)obj)->effect.type == SPHERE)
	{
		return (normalize((sub_vec(((t_sphere *)obj)->origin.origin,
			ray.origin))));
	}
	return (normalize(sub_vec(((t_sphere *)obj)->origin.origin, ray.origin)));
}

void			send_ray_ext(t_thread *data, t_vec ray, t_ray *r)
{
	r->tmp.origin = set_neworigin_neg(ray, r->dist[0]);
	r->tmp.direction = veccpy(ray.direction);
	r->tmp.direction = find_normal_with_txt(data, r->obj, r->tmp);
}

static void		init_sray(t_sray *s, t_thread *data, t_vec *ray, t_ray *r)
{
	s->data = data;
	s->ray = ray;
	s->r = r;
	s->save = NULL;
	s->save2 = NULL;
	s->data->sub = 0;
}

unsigned int	send_ray22_ext(t_sray *s)
{
	while (((t_base *)s->r->obj) != s->save)
	{
		if (s->save == NULL)
			s->save = s->r->obj;
		if (s->r->obj != s->save && s->save2 == NULL)
			s->save2 = s->r->obj;
		else if (s->r->obj == s->save2)
			s->save2 = NULL;
		s->ray->origin = set_neworigin_op(*(s->ray), s->r->dist[0]);
		if (!(s->r->obj = check_object(s->data, *(s->ray),
			&(s->r->dist[0]), NULL))
			|| s->r->dist[0] == -1)
			return (s->data->ambiant);
	}
	return (s->data->ambiant + 1);
}

unsigned int	send_ray22(t_thread *data, t_vec *ray,
					t_ray *r)
{
	t_sray	s;

	init_sray(&s, data, ray, r);
	if (((t_base *)r->obj)->effect.sub)
	{
		if ((s.res = send_ray22_ext(&s)) == s.data->ambiant)
			return (data->ambiant);
		ray->origin = set_neworigin_op(*ray, r->dist[0]);
		if (s.save2 != NULL && ((t_base *)s.save2)->effect.type != OBJ)
		{
			data->sub = 1;
			data->normal_sub = normal_sub(*ray, s.save2);
		}
		else
			data->sub = 0;
		if (!(r->obj = check_object(data, *ray, &(r->dist[0]), NULL))
			|| r->dist[0] == -1)
			return (data->ambiant);
	}
	return (0);
}
