/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_framed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:32:01 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/26 18:54:39 by lomasse          ###   ########.fr       */
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
	if (!(fake = ft_strjoinfree(fake, ".bmp", 1)))
		return (NULL);
	name ? free(name) : 0;
	name = ft_strdup(fake);
	fake ? free(fake) : 0;
	return (name);
}

static char		*next_frame(t_data *data, char *name)
{
	int		nb;
	char	*fake;
	char	*fake2;

	if (!(fake = ft_strdup(name)))
		return (NULL);
	if (*ft_strrchr(fake, '.'))
		*ft_strrchr(fake, '.') = '\0';
	nb = ft_atoi(ft_strrchr(fake, '_') + 1);
	nb += 1;
	if (!(fake2 = ft_strdup(fake)))
		return (NULL);
	if (*(ft_strrchr(fake2, '_') + 1))
		*(ft_strrchr(fake2, '_') + 1) = '\0';
	if (!(fake2 = ft_strjoinfree(fake2, ft_itoa(nb), 2)))
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
		path = ft_strdup("./Screenshot/Render_0\0");
		path = findcurrentdirname(path);
		path = ft_strjoinfree(path, "/Frame_0.bmp\0", 1);
	}
	if (!(surface = SDL_LoadBMP(path)))
		ft_putstr("No file to load\n");
	txt = SDL_CreateTextureFromSurface(data->window.rend, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(data->window.rend, txt, NULL, NULL);
	SDL_DestroyTexture(txt);
	path = next_frame(data, path);
	if (data->flag.asked && !data->flag.show)
	{
		free(path);
		path = NULL;
		data->flag.show = 0;
	}
}

static void		stop_frame(t_data *data, char **path)
{
	ft_putstr("Attention, Rendu Indisponible");
	ft_putstr(" (Creation du dossier impossible)\n");
	free(*path);
	*path = NULL;
	data->flag.show = 0;
	data->flag.save = 0;
}

void			framed(t_data *data)
{
	static char	*path = NULL;

	if (path == NULL && data->flag.save)
		path = ft_strdup("./Screenshot/Render_0\0");
	if (data->flag.video == data->flag.nb_video && path != NULL)
	{
		check_folder_screenshot();
		path = finddirname(path);
		if (mkdir(path, 0777))
		{
			stop_frame(data, &path);
			return ;
		}
		path = ft_strjoinfree(path, "/Frame_0\0", 1);
	}
	else if (data->flag.video != 0 && path != NULL && data->flag.save)
		create_screenshot_bmp(data, data->window.pxl, &path, 0);
	if (data->flag.video == 1 && path != NULL)
	{
		free(path);
		path = NULL;
		data->flag.show = 1;
		data->flag.asked = 0;
		data->flag.save = 0;
	}
}
