/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:33:09 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 22:35:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <sys/types.h>

char		*finddirname(char *name)
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

char		*findcurrentdirname(char *name)
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
			break ;
		}
		fake = ft_strjoinfree(fake, ft_itoa(nb + 1), 3);
	}
	fake = ft_strjoinfree(fake, ft_itoa(nb), 3);
	free(name);
	name = ft_strdup(fake);
	free(fake);
	return (name);
}
