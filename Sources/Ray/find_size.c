/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:29:15 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/05 21:29:47 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

int			find_size(t_thread data, void *obj, int choose)
{
	int index;

	if (choose)
	{
		index = (((t_sphere *)obj)->effect.id_texture);
		return (((data.texture[index])->w << 16) + (data.texture[index])->h);
	}
	else
	{
		index = (((t_sphere *)obj)->effect.id_normal);
		return (((data.normal[index])->w << 16) + (data.normal[index])->h);
	}
}
