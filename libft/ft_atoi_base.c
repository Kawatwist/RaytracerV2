/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoi_base.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: luwargni <luwargni@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/12/06 18:20:09 by luwargni		  #+#	#+#			 */
/*   Updated: 2019/12/08 16:29:16 by luwargni		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"


// manque de protection et d'amelioration
int   ft_atoi_base(char *str, int base)
{
  int   i;
  int   j;
  int   nb;
  int   neg;
  char  *hex_str;
  char  *hex_str2;

  i = 0;
  j = 0;
  nb = 0;
  neg = 1;
  hex_str = "0123456789abcdef";
  hex_str2 = "0123456789ABCDEF"; //need variable qui compte et qui donne la valeur compte
  //appel fonction qui gere espace 
  if (!(base >= 2 && base <= 16))
	return (0);
  while (ft_isspace(str[i]))
	i++;
  if (str[i] == '0' && str[i + 1] == 'x')
	i = i + 2;
  //suite 
  if (str[i] == '-')
  {
	neg = -1;
	i++;
  }
  while (str[i])
  {
	if (str[i] != hex_str[j] && str[i] != hex_str2[j] && j < base)
	{
	  while (str[i] != hex_str[j] && str[i] != hex_str2[j] && j < base)
		j++;
	}
	if (str[i] == hex_str[j] || str[i] == hex_str2[j])
	{
	  nb = nb * base;
	  nb = nb + j;
	  j = 0;
	}
	i++;
  }
  return (nb * neg);
}