/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 22:24:42 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/02 22:16:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	stay_in_case(float value, float min, float max)
{
	if (value > min && value < max)
		return (value);
	return (value < min ? min : max);
}
