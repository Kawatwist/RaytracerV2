/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strnlen.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lomasse <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/12/02 15:18:02 by lomasse		   #+#	#+#			 */
/*   Updated: 2018/12/02 19:25:52 by lomasse		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_strchrlen(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}
