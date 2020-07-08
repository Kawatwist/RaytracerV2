/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:21:13 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/08 15:39:20 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void	generate_perlin(t_data *data)
{
	int		i;
	int		j;
	t_point	p;

	i = -1;
	srand(time(NULL));
	while (++i < GRADIENT)
	{
		j = -1;
		while (++j < GRADIENT)
		{
			p.x = rand();
			p.y = rand();
			p.z = 0;
			p = normalize(p);
			data->perlin[i * GRADIENT + j] = p;
		}
	}
}

void	generate_marble(float (*marble)[GRADIENT * GRADIENT])
{
	int	i;
	int	j;

	i = -1;
	while (++i < GRADIENT)
	{
		j = -1;
		while (++j < GRADIENT)
		{
			*marble[i * GRADIENT + j] = sin(i + j);
		}
	}
}

void	generate_wood(float (*wood)[GRADIENT * GRADIENT])
{
	int	i;
	int	j;

	i = -1;
	while (++i < GRADIENT)
	{
		j = -1;
		while (++j < GRADIENT)
		{
			*wood[i * GRADIENT + j] = sin(sqrt(i * i + j * j));
		}
	}
}
