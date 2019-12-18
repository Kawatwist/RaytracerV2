/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strdel.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lomasse <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/11/07 07:38:17 by lomasse		   #+#	#+#			 */
/*   Updated: 2018/11/11 05:57:54 by lomasse		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel(char **as)
{
	if (as == NULL)
		return ;
	if (*as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}
