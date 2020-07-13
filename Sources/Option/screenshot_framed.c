/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_framed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:32:01 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/08 22:52:49 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <sys/types.h>

static char		*finddirname(char *name)
{
	int		nb;
	char	*fake;

	fake = ft_strdup(name);
	while (access(fake, F_OK) == 0)
	{
		nb = ft_atoi(ft_strchr(fake, '_') + 1);
		nb += 1;
		*(ft_strchr(fake, '_') + 1) = '\0';
		fake = ft_strjoinfree(fake, ft_itoa(nb), 3);
	}
	free(name);
	name = ft_strdup(fake);
	free(fake);
	return (name);
}

static char		*next_frame(t_data *data, char *name)
{
	int		nb;
	char	*fake;
	char	*fake2;

	fake = ft_strdup(name); /* Secure malloc*/
	*ft_strrchr(fake, '.') = '\0';
	nb = ft_atoi(ft_strrchr(fake, '_') + 1);
	nb += 1;
	fake2 = ft_strdup(fake);
	*(ft_strrchr(fake2, '_') + 1) = '\0';
	fake2 = ft_strjoinfree(fake2, ft_itoa(nb), 2);
	fake2 = ft_strjoinfree(fake2, ".bmp", 1);
	if (nb == data->flag.nb_video - 1 || access(fake2, F_OK))
		nb = 0;
	free(fake2);
	*(ft_strrchr(fake, '_') + 1) = '\0';
	fake = ft_strjoinfree(fake, ft_itoa(nb), 3);
	fake = ft_strjoinfree(fake, ".bmp", 1);
	free(name);
	name = ft_strdup(fake);
	free(fake);
	return (name);
}

static char		*findcurrentdirname(char *name)
{
	int		nb;
	char	*fake;
	char	*fake2;

	fake = ft_strdup(name);
	while (access(fake, F_OK) == 0)
	{
		nb = ft_atoi(ft_strchr(fake, '_') + 1);
		*(ft_strchr(fake, '_') + 1) = '\0';
		fake2 = ft_strjoinfree(fake, ft_itoa(nb + 1), 2);
		if (access(fake2, F_OK))
		{
			free(fake2);
			break;
		}
		fake = ft_strjoinfree(fake, ft_itoa(nb + 1), 3);
	}
	fake = ft_strjoinfree(fake, ft_itoa(nb), 3);
	free(name);
	name = ft_strdup(fake);
	free(fake);
	return (name);
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
	/* Secure */

	surface = SDL_LoadBMP(path);
	txt = SDL_CreateTextureFromSurface(data->window.rend, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(data->window.rend, txt, NULL, NULL);
	SDL_RenderPresent(data->window.rend);
	SDL_DestroyTexture(txt);
	path = next_frame(data, path);
	if (data->flag.asked)
	{
		free(path);
		path = NULL;
		data->flag.show = 0;
	}
}

static void		stop_frame(t_data *data, char **path)
{
	ft_putstr("Attention, Rendu Indisponible (Creation du dossier impossible)\n");
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
		path = finddirname(path);
		if (mkdir(path, 0777))
		{
			stop_frame(data, &path);
			return ;
		}
		path = ft_strjoinfree(path, "/Frame_0\0", 1);
	}
	else if (data->flag.video != 0 && path != NULL && data->flag.save)
	{
		printf("Screenshot name : %s\n", path);
		create_screenshot_bmp(data, data->window.pxl, &path, 0);
	}
	if (data->flag.video == 1 && path != NULL)
	{
		free(path);
		path = NULL;
		data->flag.show = 1;
		data->flag.asked = 0;
		data->flag.save = 0;
	}
}
