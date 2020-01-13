/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:06:18 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/13 20:06:51 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*strcpy_between_2c(char *src, char c1, char c2)
{
	char	*str;
	size_t	size;
	int		i;
	int		j;

	if (!src)
		return (NULL);
	size = 0;
	i = 0;
	j = 0;
	while (src[i] && src[i] != c1)
		i++;
	while (src[i] && src[i + 1] != c2)
	{
		i++;
		size++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (size) + 1)))
		return (NULL);
	i = i - size;
	while (size--)
		str[j++] = src[++i];
	str[j] = '\0';
	return (str);
}

t_point		get_point(char *str)
{
	t_point		pointf;
	char		*line;

	line = strcpy_between_2c(str, '{', '}');
	pointf.x = ft_atof(line);
	pointf.y = ft_atof(ft_strchr(line, ' ') + 1);
	pointf.z = ft_atof(ft_strrchr(line, ' ') + 1);
	free(line);
	return (pointf);
}
