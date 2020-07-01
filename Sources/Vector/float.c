/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 22:24:42 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/28 22:27:17 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	stay_in_case(float	value, float min, float max)
{
	if (value > min && value < max)
		return (value);
	return (value < min ? min : max);
}
