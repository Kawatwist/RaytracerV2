/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:01:37 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/13 22:01:38 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			key_old(t_data data, int mask)
{
	if (data.input.key[mask] && data.input.oldkey[mask])
		return (1);
	return (0);
}

char			key_check(t_data data, int mask)
{
	if (data.input.key[mask] && !data.input.oldkey[mask])
		return (1);
	return (0);
}
