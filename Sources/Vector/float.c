/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 22:24:42 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/25 13:12:43 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int		maxu(unsigned int value, unsigned int value2)
{
	return (value < value2 ? value2 : value);
}

unsigned int		lowu(unsigned int value, unsigned int value2)
{
	return (value < value2 ? value : value2);
}
