/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/18 17:30:09 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "error.h"

static char		*find_error(int error_value)
{
	static char *err[] = {NULL, ERR_MALLOC, ERR_WINDOW, ERR_SURFACE, ERR_TXT,
			ERR_RENDER, ERR_KEYBOARD, ERR_MOUSE, ERR_EMPTY, ERR_PATH,
			ERR_HEADER, ERR_TYPE, ERR_UNINDEXED};

	error_value >= 12 ? error_value = 12 : 0;
	error_value < 0 ? error_value = 12 : 0;
	return (err[error_value]);
}

/*
**	Can't Stop the Program properly
*/

void			stop_execute(char *error, t_data *data)
{
	(void)data;
	ft_putstr(error);
	exit(0);
}

/*
**	End of the main if something went wrong
*/

int				stop_main_execute(char *error, t_data *data, int error_value)
{
	ft_putstr(error);
	ft_putstr("Erreur ");
	ft_putnbr(error_value);
	if (error[6] == 'P')
	{
		ft_putstr("\tline : ");
		ft_putnbr(data->parse.error_line + 1);
	}
	ft_putstr(find_error(error_value));
	clear_memory(data);
	return (error_value);
}
