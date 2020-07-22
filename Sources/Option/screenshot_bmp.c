/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 18:53:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 22:32:42 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_folder_screenshot(void)
{
	if (access("./Screenshot", F_OK))
		if (mkdir("./Screenshot", 0777))
			ft_putstr("Creation du dossier Screenshot impossible\n");
}

static char	*findname_bmp(char *name)
{
	int		nb;
	char	*fake;

	fake = ft_strjoin(name, ".bmp");
	while (access(fake, F_OK) == 0)
	{
		nb = ft_atoi(ft_strrchr(fake, '_') + 1);
		nb += 1;
		*(ft_strrchr(fake, '_') + 1) = '\0';
		fake = ft_strjoinfree(fake, ft_itoa(nb), 3);
		fake = ft_strjoinfree(fake, ".bmp", 1);
	}
	free(name);
	name = ft_strdup(fake);
	free(fake);
	return (name);
}

static void	screenshot_bmp_2(t_data *data, char **path, char *name, int mode)
{
	if (mode == 1)
	{
		if (name)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Screenshot Done", name, data->window.window);
		name ? free(name) : 0;
		*path ? free(*path) : 0;
	}
	else
		name ? free(name) : 0;
}

void		create_screenshot_bmp(t_data *data, void *pxl,
		char **path, int mode)
{
	char			*name;
	SDL_Surface		*tobmp;

	check_folder_screenshot();
	name = ft_strdup(*path);
	name = findname_bmp(name);
	tobmp = SDL_CreateRGBSurfaceWithFormatFrom(pxl, data->window.x,
		data->window.y, 32, data->window.x * 4, SDL_PIXELFORMAT_BGRA32);
	if (tobmp != NULL)
	{
		if (SDL_SaveBMP(tobmp, name))
		{
			SDL_FreeSurface(tobmp);
			ft_putstr("Screenshot impossible\n");
			name ? free(name) : 0;
			return ;
		}
		SDL_FreeSurface(tobmp);
	}
	screenshot_bmp_2(data, path, name, mode);
}
