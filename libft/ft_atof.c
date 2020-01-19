/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:02:18 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/19 21:02:33 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_zero(const char *str)
{
	int		count;

	count = 0;
	while (str[count] && str[count] == '0')
		count++;
	return (count);
}

static double	check_sign(const char **nptr, int *flag)
{
	if (!(*nptr) || *(*nptr) == '\0')
		return (0.0);
	if (*(*nptr) == '-' || *(*nptr) == '+')
	{
		(*flag) = (*(*nptr) == '-' ? 0b1000000000000000000000000 : 0);
		(*nptr)++;
	}
	while ((*nptr)[(*flag) & 0xFF] && (((*nptr)[(*flag) & 0xFF] >= '0' &&
	(*nptr)[(*flag) & 0xFF] <= '9') || (*nptr)[(*flag) & 0xFF] == '.'))
		(*flag) += 1;
	if (!((*nptr)[(*flag) & 0xFF] == '\0' || ((*nptr)[(*flag) & 0xFF] == ' ')))
		return (0.0);
	return (1);
}

static void		get_nbr2(const char *nptr, double *nbr2,
long long tmp, int *flag)
{
	int			nb_0;

	(*nbr2) = (double)ft_atoi(&(nptr[((*flag) & 0xFF) + 1]));
	tmp = (*nbr2);
	while (tmp)
	{
		tmp /= 10;
		(*flag) += (1 << 8);
	}
	tmp = 1;
	while (((*flag) & 0xFF00))
	{
		tmp *= 10;
		(*flag) -= (1 << 8);
	}
	nb_0 = count_zero(&(nptr[((*flag) & 0xFF) + 1]));
	while (nb_0)
	{
		tmp *= 10;
		nb_0--;
	}
	(*nbr2) /= tmp;
}

double			ft_atof(const char *nptr)
{
	double		nbr;
	double		nbr2;
	long long	tmp;
	int			flag;

	nbr2 = 0.0;
	flag = 0;
	if ((check_sign(&nptr, &flag)) != 1)
		return (0.0);
	else
	{
		nbr = (double)ft_atoi(nptr);
		flag -= (flag & 0xFF);
		while (nptr[flag & 0xFF] != '.' &&
		nptr[flag & 0xFF] != '\0' && nptr[flag & 0xFF] != ' ')
			flag += 1;
		if ((flag & 0xFF) != 0 && nptr[flag & 0xFF] == '.')
			get_nbr2(nptr, &nbr2, tmp, &flag);
	}
	nbr = nbr + nbr2;
	if (flag & 0x1000000)
		nbr *= -1;
	return (nbr);
}
