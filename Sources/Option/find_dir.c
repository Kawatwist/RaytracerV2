/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:33:09 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/28 14:19:50 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <sys/types.h>

char		*finddirname(void)
{
	int		nb;
	char	*fake;

	if (!(fake = ft_strdup("./Screenshot/Render_0\0")))
		return (NULL);
	while (access(fake, F_OK) == 0)
	{
		nb = ft_atoi(ft_strchr(fake, '_') + 1);
		nb += 1;
		*(ft_strchr(fake, '_') + 1) = '\0';
		fake = ft_strjoinfree(fake, ft_itoa(nb), 3);
	}
	return (fake);
}

char		*findcurrentdirname(void)
{
	int		nb;
	char	*fake;
	char	*fake2;

	if (!(fake = ft_strdup("./Screenshot/Render_0\0")))
		return (NULL);
	while (access(fake, F_OK) == 0)
	{
		nb = ft_atoi(ft_strchr(fake, '_') + 1);
		*(ft_strchr(fake, '_') + 1) = '\0';
		fake2 = ft_strjoinfree(fake, ft_itoa(nb + 1), 2);
		if (access(fake2, F_OK))
		{
			fake2 ? free(fake2) : 0;
			break ;
		}
		fake2 ? free(fake2) : 0;
		fake = ft_strjoinfree(fake, ft_itoa(nb + 1), 3);
	}
	fake = ft_strjoinfree(fake, ft_itoa(nb), 3);
	return (fake);
}
