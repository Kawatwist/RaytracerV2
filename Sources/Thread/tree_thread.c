/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 22:33:10 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/11 22:24:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <thread.h>

void			setup_effect(t_thread *data, t_tree *curr)
{
	if (curr->reflexion != NULL && curr->refraction != NULL && curr->opacity != NULL)
	{
		if (((t_base *)curr->obj)->effect.reflection > 0)
		{
			curr->reflexion->percent = ((t_base *)curr->obj)->effect.reflection;
			curr->reflexion->cam.origin = set_neworigin_neg(curr->cam, curr->dist);
			curr->reflexion->cam.direction = find_reflexion(curr->obj, curr->cam, *data);
		}
		else
		{
			curr->reflexion->percent = 0;
			curr->reflexion->done = 2;
		}
		if (((t_base *)curr->obj)->effect.refraction > 0)
		{
			curr->refraction->percent = ((t_base *)curr->obj)->effect.refraction;
			curr->reflexion->cam.origin = set_neworigin_op(curr->cam, curr->dist);
			curr->reflexion->cam.direction = find_refraction(*data, curr->obj, curr->cam);
		}
		else
		{
			curr->refraction->percent = 0;
			curr->refraction->done = 2;
		}
		if (((t_base *)curr->obj)->effect.opacity > 0)
		{
			curr->opacity->percent = ((t_base *)curr->obj)->effect.opacity;
			curr->reflexion->cam.origin = set_neworigin_op(curr->cam, curr->dist);
			curr->opacity->cam.direction = veccpy(curr->cam.direction);
		}
		else
		{
			curr->opacity->percent = 0;
			curr->opacity->done = 2;
		}
		curr->done = 2;
	}
	else
		curr->done = 3;
}

unsigned int	send_ray_branch(t_thread *data, t_tree **curr)
{
	if (!((*curr)->obj = check_object(data, (*curr)->cam, &((*curr)->dist))) || (*curr)->dist == -1)
	{
		(*curr)->done = 0;
		return (data->ambiant);
	}
	(*curr)->collide.origin = set_neworigin((*curr)->cam, (*curr)->dist);
	if (((data->dist_ray = length(sub_vec((*curr)->collide.origin, (*curr)->cam.origin))) >
		data->max_dist) && data->max_dist)
	{
		(*curr)->done = 0;
		return (data->ambiant);
	}
	(*curr)->collide.direction = veccpy((*curr)->cam.direction);
	(*curr)->color = find_color(data, (*curr)->obj, (*curr)->collide);
	data->tmp_color = (*curr)->color;
	(*curr)->collide.origin = set_neworigin_neg((*curr)->cam, (*curr)->dist);
	(*curr)->collide.direction = veccpy((*curr)->cam.direction);
	(*curr)->collide.direction = find_normal_with_txt(*data, (*curr)->obj, (*curr)->collide);
	setup_effect(data, (*curr));
	if (data->flag.normal)
		(*curr)->color = (int)(((*curr)->collide.direction.x + 1) * (255 / 2.0)) +
			((int)(((*curr)->collide.direction.y + 1) * (255 / 2.0)) << 8) +
			((int)(((*curr)->collide.direction.z + 1) * (255 / 2.0)) << 16);
	return ((*curr)->color);
}

static t_tree	*find_lower_branch(t_tree **curr, int value)
{
	if ((*curr)->reflexion && (*curr)->reflexion->done != value)
		return ((*curr)->reflexion);
	if ((*curr)->refraction && (*curr)->refraction->done != value)
		return ((*curr)->refraction);
	if ((*curr)->opacity && (*curr)->opacity->done != value)
		return ((*curr)->opacity);
	if ((*curr))
		(*curr)->done = value;
	return ((*curr));
}

unsigned int	color_tree(t_thread *data, int bounce, t_tree *tree)
{
	(void)bounce;
	(void)tree;
	t_tree			*curr;
	t_tree			*tmp;

	curr = data->tree;
	while (data->tree->done != 3)
	{
		while (curr->done != 3)
		{
			if (curr->reflexion && curr->refraction && curr->opacity)
			{
				if (curr->reflexion->done == 3 && curr->refraction->done == 3 && curr->opacity->done == 3)
				{
					if (curr->before && curr)
						curr->before->color = set_color(curr->before->color, curr->color, curr->percent / 255.0, -1);
				}
			}
			else if (curr->before && curr)
				curr->before->color = set_color(curr->before->color, curr->color, curr->percent / 255.0, -1);
			tmp = curr;
			curr = find_lower_branch(&curr, 3);
			if (curr == tmp)
				curr->done = 3;
		}
		if (curr && curr->before)
			curr = curr->before;
		else
			return (data->tree->color);
	}
	return (data->tree->color);
}

void			send_ray_tree(t_thread *data, t_vec ray)
{
	t_tree	*curr;

	curr = data->tree;
	curr->cam.origin = veccpy(ray.origin);
	curr->cam.direction = veccpy(ray.direction);
	curr->percent = 1;
	while (data->tree->done != 2)
	{
		if (curr == NULL)
			break;
		while (curr->done != 2)
		{
			curr->color = send_ray_branch(data, &curr);
			curr = find_lower_branch(&curr, 2);
		}
		curr = curr->before;
	}
}

unsigned int	tree_thread(t_thread *data, t_vec ray, int bounce)
{
	unsigned int color;

	(void)bounce;
	send_ray_tree(data, ray);
	color = color_tree(data, data->bounce, data->tree);
	return (color);
}
