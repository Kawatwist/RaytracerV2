/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 18:53:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/20 15:34:47 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void		create_screenshot_bmp(t_data *data, void *pxl, char **path, int mode)
{
	char			*name;
	SDL_Surface		*tobmp;

	name = ft_strdup(*path);
	name = findname_bmp(name);
	tobmp = SDL_CreateRGBSurfaceWithFormatFrom(pxl, data->window.x,
		data->window.y, 32, data->window.x * 4, SDL_PIXELFORMAT_BGRA32);
	printf("Screenshot Path Current: %s\n", name);
	printf("Screenshot : %d\n", SDL_SaveBMP(tobmp, name));
    printf("Screenshot error: %s\n", SDL_GetError());
	if (tobmp != NULL)
		SDL_FreeSurface(tobmp);
	if (mode == 1)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			"Screenshot Done", name, data->window.window);
		free(name);
	}
	else
	{
		// if (path)
		// 	free(path);
		// *path = name;
		// *(ft_strrchr(*path, '/')+ 1) = '\0';
	}
}
