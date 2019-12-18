/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   count_c.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: luwargni <luwargni@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/12/07 18:22:13 by luwargni		  #+#	#+#			 */
/*   Updated: 2019/12/08 15:43:48 by luwargni		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

unsigned int		count_c(char *src, char c)
{
	unsigned int		size;

	size = 0;
	while (*src)
		if (*src++ == c)
			size++;
	return (size);
}