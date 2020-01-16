/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/16 00:00:14 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char		*find_error(int error_value)
{
	if (error_value == 1)
		return ("\nMemory allocation failed\n");
	if (error_value == 2)
		return ("\nCan't Create SDL_Window\n");
	if (error_value == 3)
		return ("\nCan't Create SDL_Surface\n");
	if (error_value == 4)
		return ("\nSDL_Texture Error\n");
	if (error_value == 5)
		return ("\nSDL_Render Failed\n");
	if (error_value == 6)
		return ("\nKeyboards Input Error\n");
	if (error_value == 7)
		return ("\nMouse Input Error\n");
	if (error_value == 10)
		return ("\nEmpty map\n");
	if (error_value == 11)
		return ("\nIncorrect Path name\n");
	if (error_value == 12) //faire
		return ("\nIncorrect Header\n");
	if (error_value == 13)
		return ("\nIncorrect Nb_types\n");
	if (error_value == 14)
		return ("\nIncorrect path name\n");
	if (error_value == 15)
		return ("\nIncorrect path name\n");
	if (error_value == 16)
		return ("\nIncorrect path name\n");
	if (error_value == 17)
		return ("\nIncorrect path name\n");
	if (error_value == 18)
		return ("\nIncorrect path name\n");
	if (error_value == 19)
		return ("\nIncorrect path name\n");
	if (error_value == 20)
		return ("\nIncorrect path name\n");

	if (error_value > 11)
		printf("\nC'est trop la !\n");
	return ("\nUnindexed Error\n");
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
	(void)data;
	ft_putstr(error);
	ft_putstr("Erreur ");
	ft_putnbr(error_value);
	if (error[6] == 'P')
	{
		ft_putstr("\tline : ");
		ft_putnbr(data->parse.error_line + 1);
	}
	ft_putstr(find_error(error_value));
	return (error_value);
}
