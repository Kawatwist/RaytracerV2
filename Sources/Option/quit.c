/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/06 04:20:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"
#include "error.h"

static char		*find_error(int error_value)
{
	static char *err[] = {NULL, ERR_MALLOC, ERR_WINDOW, ERR_SURFACE, ERR_TXT,
			ERR_RENDER, ERR_KEYBOARD, ERR_MOUSE, ERR_EMPTY, ERR_PATH,
			ERR_HEADER, ERR_NB_TYPE, ERR_TEXTURES, ERR_IN_LIGHT, ERR_IN_CAM,
			ERR_IN_OBJ, ERR_NAME, ERR_TYPE, ERR_THREAD, ERR_UNINDEXED};

	error_value >= 19 ? error_value = 19 : 0;
	error_value < 0 ? error_value = 19 : 0;
	return (err[error_value]);
}

/*
**	Can't Stop the Program properly
*/

int			stop_execute(char *error, t_data *data)
{
	int		i;

	i = -1;
	while (++i < 4)
		pthread_cancel(((t_thread *)data->thread)[i].thd);
	ft_putstr(error);
	return (18);
}

/*
**	End of the main if something went wrong
*/

int				stop_main_execute(char *error, t_data *data, int error_value)
{
	ft_putstr(error);
	if (error_value != 18)
	{
		ft_putstr("Erreur ");
		ft_putnbr(error_value);
	}
	if (error[6] == 'P')
	{
		ft_putstr("\tline : ");
		ft_putnbr(data->parse.error_line + 1);
	}
	ft_putstr(find_error(error_value));
	clear_memory(data);
	return (error_value);
}
