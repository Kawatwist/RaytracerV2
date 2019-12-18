/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putchar_fd.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lomasse <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/11/07 09:48:10 by lomasse		   #+#	#+#			 */
/*   Updated: 2018/11/08 04:30:29 by lomasse		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
