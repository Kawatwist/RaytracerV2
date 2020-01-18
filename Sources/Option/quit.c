/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/18 16:59:11 by lomasse          ###   ########.fr       */
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

void		clear_texture(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_texture - 1)
		(tofree)[i] != NULL ? free_tga((tofree)[i]) : 0;
	free((tofree));
}

void		clear_obj_item(t_data *data, t_object tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_item)
		tofree.item[i] != NULL ? free(tofree.item[i]) : 0;
	free(tofree.item);
}

void		clear_normal(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_normal - 1)
		(tofree)[i] != NULL ? free_tga((tofree)[i]) : 0;
	free((tofree));
}

void		clear_obj_cam(t_object tofree)
{
	tofree.camera != NULL ? free(tofree.camera) : 0;
}

void		clear_obj_light(t_object tofree)
{
	tofree.light != NULL ? free(tofree.light) : 0;
}

int				clear_memory(t_data *data, SDL_Renderer *r)
{
	clear_texture(data, data->texture);
	clear_obj_item(data, data->obj);
	clear_normal(data, data->normal);
	clear_obj_cam(data->obj);
	clear_obj_light(data->obj);

	SDL_DestroyTexture(data->window.txt);
	SDL_DestroyRenderer(data->window.rend);
	SDL_DestroyWindow(data->window.window);
	SDL_Quit();
	sleep(5);
	(void)r;
	return (0);
}

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
	//clear_memory(data, data->dinwo);
	return (error_value);
}
