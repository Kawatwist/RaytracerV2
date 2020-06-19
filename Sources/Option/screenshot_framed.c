/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_framed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:32:01 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/19 21:02:20 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <sys/types.h>

static char	*finddirname(char *name)
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
	name = ft_strjoinfree(name, "/", 1);
	return (name);
}

void	framed(t_data *data)
{
	static char	*path = NULL;

	printf("path : %s\n", path);
	if (path == NULL)
		path = ft_strdup("./Screenshot/Render_0\0");
	if (data->flag.video == 31 && path != NULL)
	{
		path = finddirname(path);
		mkdir(path, 0777);
		path = ft_strjoinfree(path, "Frame_0\0", 1);
	}
	else if (data->flag.video != 0 && path != NULL)
	{
		create_screenshot_bmp(data, data->window.pxl, &path, 0);
	}
	if (data->flag.video == 0 && path != NULL)
	{
		free(path);
		path = NULL;
	}
}
