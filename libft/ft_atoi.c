/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoi.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: luwargni <luwargni@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/11/07 06:27:55 by lomasse		   #+#	#+#			 */
/*   Updated: 2019/11/26 20:40:28 by luwargni		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *nptr)
{
	int	negative;
	int	nb;

	nb = 0;
	negative = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
		negative = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr - '0');
		nptr++;
	}
	return (nb * negative);
}
