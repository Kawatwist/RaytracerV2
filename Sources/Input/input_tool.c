/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:01:37 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/29 13:51:12 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			mouse_hold(t_data *data, Uint32 mask)
{
	if ((data->input.button & mask) && !(data->input.oldbutton & mask))
		return (1);
	return (0);
}

char			mouse_check(t_data *data, Uint32 mask)
{
	if ((data->input.button & mask) && !(data->input.oldbutton & mask))
		return (1);
	return (0);
}

char			key_hold(t_data *data, Uint32 mask)
{
	if (data->input.key[mask] && data->input.oldkey[mask])
		return (1);
	return (0);
}

char			key_check(t_data *data, Uint32 mask)
{
	if (data->input.key[mask] && !data->input.oldkey[mask])
		return (1);
	return (0);
}
