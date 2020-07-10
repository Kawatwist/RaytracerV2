/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 00:33:58 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/10 02:06:47 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <thread.h>

static int		create_sub_tree(t_tree *curr)
{
	if (!(curr->reflexion = malloc(sizeof(t_tree))))
		return (1);
	ft_bzero(curr->reflexion, sizeof(t_tree));
	if (!(curr->refraction = malloc(sizeof(t_tree))))
		return (1);
	ft_bzero(curr->refraction, sizeof(t_tree));
	if (!(curr->opacity = malloc(sizeof(t_tree))))
		return (1);
	ft_bzero(curr->opacity, sizeof(t_tree));
	curr->reflexion->before = curr;
	curr->refraction->before = curr;
	curr->opacity->before = curr;
	return (0);
}

static int	setup_first_branch(t_data *data, t_thread *thd, t_tree **pos)
{
	int		nb_bounce;
	t_tree	*curr;

	if (!(thd->tree = malloc(sizeof(t_tree))))
		return (1);
	ft_bzero(thd->tree, sizeof(t_tree));
	thd->tree->first = 1;
	nb_bounce = 0;
	curr = thd->tree;
	while (nb_bounce < data->bounce + 1)
	{
		if ((create_sub_tree(curr)))
			return (1);
		curr->reflexion->before = curr;
		curr = curr->reflexion;
		nb_bounce += 1;
	}
	*pos = curr;
	return (0);
}

static int	reach_top(t_tree *curr, int bounce)
{
	int		deep;

	deep = 0;
	while ((deep < bounce) || (!curr->reflexion->done || !curr->refraction->done || !curr->opacity))
	{
		int value = deep;
		while (value-- > 0)
			printf("\t");
		if (curr == curr->before->reflexion)
			printf("reflexion\n");
		if (curr == curr->before->refraction)
			printf("refraction\n");
		if (curr == curr->before->opacity)
			printf("opacity\n");
		if (deep == 0)
		{
			curr->reflexion = NULL;
			curr->refraction = NULL;
			curr->opacity = NULL;
			curr->done = 1;
			curr = curr->before;
			deep += 1;
		}
		else if (curr->reflexion->done && curr->refraction->done && curr->opacity->done)
		{
			curr->done = 1;
			curr = curr->before;
			deep += 1;
		}
		else
		{
			if (!curr->reflexion->done)
				curr = curr->reflexion;
			else if (!curr->refraction->done)
				curr = curr->refraction;
			else if (!curr->opacity->done)
				curr = curr->opacity;
			if (create_sub_tree(curr))
				return (1);
			deep -= 1;
		}
	}
	return (0);
}

int			setup_tree(t_data *data, t_thread *thd)
{
	int		current_thread;
	t_tree	*curr;

	current_thread = -1;
	while (++current_thread < 4)
	{
		if (setup_first_branch(data, &(thd[current_thread]), &curr))
			return (1);
		if (reach_top(curr, thd[current_thread].bounce))
			return (1);
	}
	return (0);
}

void		reset_tree(t_data *data, t_thread *thd)
{
	(void)data;
	int		current_thread;
	t_tree	*curr;

	current_thread = -1;
	while (++current_thread < 4)
	{
		curr = thd[current_thread].tree;
		while (thd[current_thread].tree->reflexion || thd[current_thread].tree->refraction || thd[current_thread].tree->opacity)
		{
			if (curr->reflexion->done)
				curr = curr->reflexion;
			else if (curr->refraction->done)
				curr = curr->refraction;
			else if (curr->opacity->done)
				curr = curr->opacity;
		}
	}
}
