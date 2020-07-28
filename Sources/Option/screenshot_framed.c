/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_framed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:32:01 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/28 15:55:58 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <sys/types.h>

static char		*next_frame_2(int nb, char *name, char *fake, char *fake2)
{
	fake2 ? free(fake2) : 0;
	if (*(ft_strrchr(fake, '_') + 1))
		*(ft_strrchr(fake, '_') + 1) = '\0';
	if (!(fake = ft_strjoinfree(fake, ft_itoa(nb), 3)))
		return (NULL);
	if (!(name = ft_strjoinfree(fake, ".bmp", 1)))
		return (NULL);
	return (name);
}

static char		*next_frame(t_data *data, char *name)
{
	int		nb;
	char	*fake;
	char	*fake2;

	if (!(fake = ft_strjoinfree(name, "\0", 1)))
		return (NULL);
	if (*ft_strrchr(fake, '.'))
		*ft_strrchr(fake, '.') = '\0';
	nb = ft_atoi(ft_strrchr(fake, '_') + 1);
	nb += 1;
	if (!(fake2 = ft_strdup(fake)))
		return (NULL);
	if (*(ft_strrchr(fake2, '_') + 1))
		*(ft_strrchr(fake2, '_') + 1) = '\0';
	if (!(fake2 = ft_strjoinfree(fake2, ft_itoa(nb), 3)))
		return (NULL);
	if (!(fake2 = ft_strjoinfree(fake2, ".bmp", 1)))
		return (NULL);
	if (nb == data->flag.nb_video - 1 || access(fake2, F_OK))
		nb = 0;
	return (next_frame_2(nb, name, fake, fake2));
}

void			show_framed(t_data *data)
{
	static char	*path = NULL;
	SDL_Texture	*txt;
	SDL_Surface	*surface;

	if (path == NULL)
	{
		path = findcurrentdirname();
		if (path == NULL)
			return ;
		path = ft_strjoinfree(path, "/Frame_0.bmp\0", 1);
	}
	if (!(surface = SDL_LoadBMP(path)))
		ft_putstr("No file to load\n");
	if (!(txt = SDL_CreateTextureFromSurface(data->window.rend_video, surface)))
		ft_putstr("Can't Create texture from screenshot\n");
	if (SDL_RenderCopy(data->window.rend_video, txt, NULL, NULL) < 0)
		ft_putstr("RenderCopy Failed\n");
	SDL_RenderPresent(data->window.rend_video);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(txt);
	path = next_frame(data, path);
	if (data->flag.asked && !data->flag.show)
		ft_memdel(((void**)&path));
	if (data->flag.asked && !data->flag.show)
		data->flag.show = 0;
}

static void		stop_frame(t_data *data, char **path)
{
	ft_putstr("Attention, Rendu Indisponible");
	ft_putstr(" (Creation du dossier impossible)\n");
	*path ? free(*path) : 0;
	*path = NULL;
	data->flag.show = 0;
	data->flag.save = 0;
}

void			framed(t_data *data)
{
	static char	*path = NULL;

	if (data->flag.video == data->flag.nb_video && path == NULL)
	{
		check_folder_screenshot();
		path = finddirname();
		if (mkdir(path, 0777))
		{
			stop_frame(data, &path);
			return ;
		}
		path = ft_strjoinfree(path, "/Frame_0\0", 1);
	}
	if (data->flag.video != 0 && path != NULL && data->flag.save)
		create_screenshot_bmp(data, data->window.pxl, &path, 0);
	if (data->flag.video == 1 && path != NULL)
	{
		path ? free(path) : 0;
		path = NULL;
		data->flag.start_show = 1;
		data->flag.asked = 0;
		data->flag.save = 0;
	}
}
