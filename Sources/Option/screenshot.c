/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:43:30 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/16 19:08:13 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static char	*findname(char *name)
{
	int		len;
	char	*fake;

	fake = ft_strjoin(name, ".tga");
	while (access(fake, F_OK) == 0)
	{
		len = ft_strlen(name);
		if (name[len - 1] < '9')
			name[len - 1] += 1;
		else
			name = ft_strjoin(name, "0\0");
		free(fake);
		fake = ft_strjoin(name, ".tga");
	}
	free(fake);
	return (name);
}

static void	ft_revputnstr_fd(void *str, long int len, int fd, long int x)
{
	while (len-- > 0)
		write(fd, &(((int *)str)[((x & 0xFFFFFFFF) -
			(len % (x & 0xFFFFFFFF))) +
			((len / (x & 0xFFFFFFFF)) *
			(x >> 32)) - 1]), 4);
}

static void	ft_putnstr_fd(void *str, long int len, int fd)
{
	write(fd, str, len);
}

static void	init_head(t_data *data, unsigned char (*header)[18])
{
	(*header)[0] = 0;
	(*header)[1] = 0;
	(*header)[2] = 2;
	(*header)[3] = 0;
	(*header)[4] = 0;
	(*header)[5] = 0;
	(*header)[6] = 0;
	(*header)[7] = 0;
	(*header)[8] = 0;
	(*header)[9] = 0;
	(*header)[10] = 0;
	(*header)[11] = 0;
	(*header)[12] = (char)((data->window.x & 0xFF));
	(*header)[13] = (char)((data->window.x & 0xFF00) >> 8);
	(*header)[14] = (char)((data->window.y & 0xFF));
	(*header)[15] = (char)((data->window.y & 0xFF00) >> 8);
	(*header)[16] = 32;
	(*header)[17] = 0;
}

void		create_screenshot(t_data *data, void *pxl)
{
	int				fd;
	unsigned char	header[18];
	char			*name;

	name = ft_strdup("./Screenshot/screenshot_0\0");
	name = findname(name);
	name = ft_strjoinfree(name, ".tga", 1);
	fd = creat(name, S_IRUSR | S_IRGRP | S_IROTH);
	init_head(data, &header);
	ft_putnstr_fd(header, 18, fd);
	ft_revputnstr_fd(pxl, data->window.x * data->window.y, fd, ((long int)data->window.y << 32) + data->window.x);
	ft_putstr("Screenshot Done : ");
	ft_putstr(name);
	ft_putchar('\n');
	free(name);
}